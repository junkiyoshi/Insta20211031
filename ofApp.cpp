#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();

	this->font_size = 30;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"‚ ", u8"‚¢", u8"‚¤", u8"‚¦", u8"‚¨",
		u8"‚©", u8"‚«", u8"‚­", u8"‚¯", u8"‚±",
		u8"‚³", u8"‚µ", u8"‚·", u8"‚¹", u8"‚»",
		u8"‚½", u8"‚¿", u8"‚Â", u8"‚Ä", u8"‚Æ",
		u8"‚È", u8"‚É", u8"‚Ê", u8"‚Ë", u8"‚Ì",
		u8"‚Í", u8"‚Ð", u8"‚Ó", u8"‚Ö", u8"‚Ù",
		u8"‚Ü", u8"‚Ý", u8"‚Þ", u8"‚ß", u8"‚à",
		u8"‚â", u8"‚ä", u8"‚æ",
		u8"‚ç", u8"‚è", u8"‚é", u8"‚ê", u8"‚ë",
		u8"‚í", u8"‚ð", u8"‚ñ",
	};
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 1.2);

	ofSetColor(255);

	for (int k = 0; k < 30; k++) {

		auto location = glm::vec3(0, 0, 231 + k * 1);

		auto noise_seed = glm::vec4(ofRandom(1000), ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int i = 0; i < 5; i++) {

			ofPushMatrix();

			ofRotateZ(ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.001 + i * 0.008), 0, 1, -360, 360));
			ofRotateY(ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.001 + i * 0.008), 0, 1, -360, 360));
			ofRotateX(ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.001 + i * 0.008), 0, 1, -360, 360));

			ofTranslate(location);

			ofRotateZ(ofMap(ofNoise(ofRandom(1000),  ofGetFrameNum() * 0.0035), 0, 1, -360, 360));

			int word_index = (int)ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, 0, this->words.size() * 3) % this->words.size();
			this->font.drawString(this->words[word_index], this->font_size * -0.65, this->font_size * -0.5);

			ofPopMatrix();
		}
	}

	ofSetColor(0);
	ofDrawSphere(230);

	this->cam.end();
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}