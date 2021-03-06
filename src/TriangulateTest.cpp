#include "TriangulateTest.h"

//--------------------------------------------------------------
void TriangulateTest::setup(){
    m_allVertices.clear();
    m_staticVertices.clear();
    int gridSize = 100;
    for( int i=-200; i < ofGetWindowWidth()+200; i+=gridSize)
    {
        for(int j=-200; j< ofGetWindowHeight()+200; j+=gridSize)
        {
            addPoint(&m_staticVertices, i+0.1f*gridSize+ofRandom(0.8f)*gridSize, j+0.1*gridSize+ofRandom(0.8f)*gridSize, 0);//ofRandom(1.0f)*gridSize);
        }
    }
    m_framerateMult = 1.0f;
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    m_mouseXPos = -300;
    m_mouseYPos = -300;
}

void TriangulateTest::addPoint(vector<XYZ> *where, float x, float y, float z ){
    XYZ v;
    v.x = x;
    v.y = y;
    v.z = z;
    where->push_back(v);
}

//--------------------------------------------------------------
void TriangulateTest::update(){
    m_framerateMult = 60.0f/(1.0f/ofGetLastFrameTime());  // compute a FPS depended factor for Animation

    float nudgeCloserFactor = 0.001;
    for(int i=0; i < m_staticVertices.size();i++)
    {
        float dist = pow(m_mouseXPos-m_staticVertices[i].x,2)+pow(m_mouseYPos- m_staticVertices[i].y, 2) ;
        if (dist < 150000 && dist > 40000) {
            m_staticVertices[i].x += ( m_mouseXPos - m_staticVertices[i].x)*nudgeCloserFactor;
            m_staticVertices[i].y += ( m_mouseYPos - m_staticVertices[i].y)*nudgeCloserFactor;
        }
    }
    /////// CLEAR OLD STUFF     
     m_triangles.clear();
     m_triangleMesh.clear();
     m_allVertices.clear();
     m_allVertices = m_staticVertices;
    
    /////// NEW COMPUTATION
     addPoint(&m_allVertices,m_mouseXPos, m_mouseYPos, 0.0f);
     int vertexCount = m_allVertices.size();
     addPoint(&m_allVertices,0.0f, 0.0f, 0.0f);
     addPoint(&m_allVertices,0.0f, 0.0f, 0.0f);
     addPoint(&m_allVertices,0.0f, 0.0f, 0.0f);
     m_triangles.resize(3*vertexCount);
     
     int ntri;
     int b = 20;
     qsort( &m_allVertices[0], m_allVertices.size()-3, sizeof( XYZ ), XYZCompare );
     Triangulate(vertexCount, &m_allVertices[0], &m_triangles[0], ntri);
     
     
     //copy vertices
     for (int i = 0; i < vertexCount; i++){
     m_triangleMesh.addVertex(ofVec3f(m_allVertices[i].x,m_allVertices[i].y,m_allVertices[i].z));
     }
     
     //copy triangles
     for(int i = 0; i < ntri; i++){
     m_triangleMesh.addIndex(m_triangles[ i ].p1);
     m_triangleMesh.addIndex(m_triangles[ i ].p2);
     m_triangleMesh.addIndex(m_triangles[ i ].p3);
     }
}

//--------------------------------------------------------------
void TriangulateTest::draw(){
  
    ofClear(50, 50, 50);
    
    // Draw Points
    ofSetColor(255, 0, 0);
    for(int i=0; i < m_allVertices.size();i++)
    {
        ofCircle(m_allVertices[i].x,m_allVertices[i].y, 1);
    }
    
    ofSetColor(0, 0, 255);
    for(int i=0; i < m_staticVertices.size();i++)
    {
        ofCircle(m_staticVertices[i].x+1.0f,m_staticVertices[i].y+1.0f, 1);
    }

    ofSetColor(220, 220, 220,200);
    m_triangleMesh.drawWireframe();
    
    
    // Draw FPS and moving Circlec
    
    ofSetColor(0, 250, 0);
    //ofCircle(m_circleXPos,m_circleYPos,60);
    string info = "fps: " + ofToString(ofGetFrameRate(),2) + "\nframerateMult: " + ofToString(m_framerateMult,2) ;
    ofDrawBitmapString(info, 5, ofGetHeight()-20);

}

//--------------------------------------------------------------
void TriangulateTest::keyPressed(int key){
    this->setup();
}

//--------------------------------------------------------------
void TriangulateTest::keyReleased(int key){

}

//--------------------------------------------------------------
void TriangulateTest::mouseMoved(int x, int y){
    m_mouseXPos = x;
    m_mouseYPos = y;
    

}

//--------------------------------------------------------------
void TriangulateTest::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void TriangulateTest::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void TriangulateTest::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void TriangulateTest::windowResized(int w, int h){

}

//--------------------------------------------------------------
void TriangulateTest::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void TriangulateTest::dragEvent(ofDragInfo dragInfo){ 

}