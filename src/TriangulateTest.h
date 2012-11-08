#pragma once

#include "ofMain.h"
#include "Delaunay.h"

class TriangulateTest : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void addPoint( float x, float y, float z );
    void addStaticPoint( float x, float y, float z );
    private:
        float m_framerateMult;
    
        vector<XYZ> m_staticVertices;
        vector<XYZ> m_allVertices;
        vector<ITRIANGLE> m_triangles;
        ofMesh m_triangleMesh;
    
        float m_circleXPos;
        float m_circleYPos;
};
