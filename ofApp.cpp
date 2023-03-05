#include "ofApp.h"

//--------------------------------------------------------------
Walker::Walker(glm::vec2 location, ofColor color) {

	this->log.push_back(location);
	this->change_rotate();

	this->color = color;
}

//--------------------------------------------------------------
void Walker::update() {

	if (glm::length(this->log.back()) > 720) {

		this->log.clear();
		auto location = glm::vec2(ofRandom(-600, 600), ofRandom(-300, 300));
		this->log.push_back(location);
		this->change_rotate();
	}

	for (int i = 0; i < 3; i++) {

		auto location = this->rotate_location + glm::vec2(this->rotate_radius * cos(this->rotate_deg * DEG_TO_RAD), this->rotate_radius * sin(this->rotate_deg * DEG_TO_RAD));
		this->rotate_deg += this->rotate_direction * 2;
		this->rotate_radius -= 0.15;

		this->log.push_back(location);
	}

	if (this->rotate_radius < 0 || ofRandom(100) < 0.15) {

		this->change_rotate();
	}

	while (this->log.size() > 250) { this->log.erase(this->log.begin()); }
}

//--------------------------------------------------------------
void Walker::change_rotate() {

	auto tmp_radius = ofRandom(30, 110);
	auto tmp_deg = this->rotate_deg + ofRandom(-90, 90);
	this->rotate_location = this->log.back() + glm::vec2(tmp_radius * cos(tmp_deg * DEG_TO_RAD), tmp_radius * sin(tmp_deg * DEG_TO_RAD));
	this->rotate_deg = 180 + tmp_deg;
	this->rotate_radius = tmp_radius;

	this->rotate_direction = ofRandom(100) < 50 ? 1 : -1;
}

//--------------------------------------------------------------
void Walker::draw_1() {

	ofSetColor(0);
	for (int i = 0; i < this->log.size() - 1; i++) {

		ofDrawCircle(this->log[i], 10);
	}
}

//--------------------------------------------------------------
void Walker::draw_2() {

	for (int i = 0; i < this->log.size() - 1; i++) {

		ofSetColor(ofColor(color));
		ofDrawCircle(this->log[i], 5);
	}
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetLineWidth(2);

	ofColor color;
	int number_of_actor = 30;
	for (int i = 0; i < number_of_actor; i++) {

		this->walker_list.push_back(Walker(glm::vec2(ofRandom(-600, 600), ofRandom(-300, 300)), ofColor(255)));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& walker : this->walker_list) {

		walker.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (auto& walker : this->walker_list) {

		walker.draw_1();
	}

	for (auto& walker : this->walker_list) {

		walker.draw_2();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}