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

		u8"あ", u8"い", u8"う", u8"え", u8"お",
		u8"か", u8"き", u8"く", u8"け", u8"こ",
		u8"さ", u8"し", u8"す", u8"せ", u8"そ",
		u8"た", u8"ち", u8"つ", u8"て", u8"と",
		u8"な", u8"に", u8"ぬ", u8"ね", u8"の",
		u8"は", u8"ひ", u8"ふ", u8"へ", u8"ほ",
		u8"ま", u8"み", u8"む", u8"め", u8"も",
		u8"や", u8"ゆ", u8"よ",
		u8"ら", u8"り", u8"る", u8"れ", u8"ろ",
		u8"わ", u8"を", u8"ん",
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