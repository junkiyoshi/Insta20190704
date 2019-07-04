#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofNoFill();
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(315);

	auto radius = 200;
	auto span = radius * 1.5;
	auto deg_span = 15;
	auto width = 100;

	vector<glm::vec3> locations  = {
		glm::vec3(-span, -span, 0), glm::vec3(0, -span, 0), glm::vec3(span, -span, 0),
		glm::vec3(-span, 0, 0), glm::vec3(span, 0, 0),
		glm::vec3(-span, span, 0), glm::vec3(0, span, 0), glm::vec3(span, span, 0)
	};

	vector<glm::vec3> degrees = {
		glm::vec3(0, 0, 0), glm::vec3(90, 0, 0), glm::vec3(0, 0, 0),
		glm::vec3(0, 90, 0), glm::vec3(0, 90, 0),
		glm::vec3(0, 0, 0), glm::vec3(90, 0, 0), glm::vec3(0, 0, 0)
	};

	for (int i = 0; i < locations.size() || i < degrees.size(); i++) {

		ofPushMatrix();
		ofTranslate(locations[i]);
		ofRotateX(degrees[i].x);
		ofRotateY(degrees[i].y);
		ofRotateZ(degrees[i].z);


		auto deg_start = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, -180, 180);
		for (auto deg = deg_start; deg < deg_start + 360; deg += deg_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), width * 0.5));
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), width * -0.5));
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), width * -0.5));
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), width * 0.5));

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}