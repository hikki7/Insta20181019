#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(239);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	int font_size = 350;
	font.loadFont("fonts/Kazesawa-Bold.ttf", font_size, true, true, true);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	string word = "A";
	font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) * 0.5);

	this->fbo.end();

	ofPixels pixels;
	this->fbo.readToPixels(pixels);

	int span = 10;

	ofColor pix_color;
	for (int x = 0; x < this->fbo.getWidth(); x += span) {

		for (int y = 0; y < this->fbo.getHeight(); y += span) {

			pix_color = pixels.getColor(x, y);
			if (pix_color != ofColor(0, 0)) {

				for (int z = span * -2; z <= span * 2; z += span) {

					this->locations.push_back(ofPoint(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.5, z));
				}
			}
		}
	}

	for (int i = 0; i < this->locations.size(); i++) {

		vector<int> next_index = vector<int>();
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j) { continue; }

			float distance = this->locations[i].distance(this->locations[j]);
			if (distance <= span) {

				next_index.push_back(j);
			}
		}

		this->next_indexes.push_back(next_index);
	}

	for (int i = 0; i < 500; i++) { this->particles.push_back(Particle(this->locations, this->next_indexes)); }
}
//--------------------------------------------------------------
void ofApp::update() {

	for (Particle& particle : particles) { particle.Upate(); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * -0.5);

	for (Particle& particle : particles) { particle.Draw(); }

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}