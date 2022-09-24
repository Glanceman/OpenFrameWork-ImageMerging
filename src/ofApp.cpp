#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	img1.loadImage("running.jpg");
	img2.loadImage("bg.jpg");
	//resize image
	mappingByResizing(img2, img1);
	
	//set up buufer
	mask.allocate(img1.getWidth(), img2.getHeight());
	mask.begin();
	ofClear(255);
	mask.end();

	//convert ot Mat 
	imgMat1 = toCv(img1);
	imgMat2 = toCv(img2);

	//set UI
	gui.setup();
	gui.add(brushSizeSlider.setup("Size", brushRadius, 1, 10));

}

//--------------------------------------------------------------
void ofApp::update(){
	mask.readToPixels(maskPixels);
	ofImage temp;
	temp.setFromPixels(maskPixels);
	temp.setImageType(OF_IMAGE_GRAYSCALE);
	maskMat=toCv(temp);
	//maskMat.convertTo(maskMat, CV_8UC3);
	//cvtColor(maskMat, maskMat, COLOR_RGBA2GRAY);
	imgMerged = merge(imgMat1, imgMat2, maskMat);
}

//--------------------------------------------------------------
void ofApp::draw(){

	drawMat(imgMerged, 0, 0);
	//mask.draw(0, 0);
	//drawMat(imgMat1, 0, 0);
	drawMat(imgMat2, img1.getWidth(), 0);
	//temp.draw(img1.getWidth(), img1.getHeight());
	//drawMat(maskMat, img1.getWidth(), img1.getHeight());

	gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	mask.begin();
	ofSetColor(0);
	ofDrawCircle(x, y, brushSizeSlider);
	mask.end();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::mappingByResizing(ofImage& source, ofImage target) {
	if ((source.getWidth() != target.getWidth()) || (source.getHeight() != target.getHeight())) {
		source.resize(target.getWidth(), target.getHeight());
	}
}

Mat ofApp::merge(Mat img, Mat bg, Mat mask) {
	Mat result(img.rows, img.cols, img.type());
	for (int i = 0; i < img.rows * img.cols; i++) {
		int r = img.data[i*3];
		int g = img.data[i*3 + 1];
		int b = img.data[i * 3 + 2];
		//cout << "r: " << r << " g: " << g << " b: " << b << endl;
		if (mask.data[i]==0 && g - r - b > 50) {
			result.data[i * 3] = bg.data[i * 3];
			result.data[i * 3 + 1] = bg.data[i * 3 + 1];
			result.data[i * 3 + 2] = bg.data[i * 3 + 2];
		}
		else {
			result.data[i * 3] = img.data[i * 3];
			result.data[i * 3 + 1] = img.data[i * 3 + 1];
			result.data[i * 3 + 2] = img.data[i * 3 + 2];
		}

	}
	return result;
}
