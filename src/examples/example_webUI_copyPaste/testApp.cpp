#include "testApp.h"
#include <Awesomium\BitmapSurface.h>

using namespace Awesomium;

void testApp::setup(){
	isResizing = false;
	webTexWidth = ofGetWindowWidth()/2;
	webTexHeight = ofGetWindowHeight()/2;
    webTex.allocate(webTexWidth, webTexHeight, GL_RGBA);
    
    // Disable scrollbars via the WebCoreConfig
	Awesomium::WebConfig config;
    //config.setCustomCSS("::-webkit-scrollbar { display: none; }");
    
	// Create our WebCore singleton with the default options
	webCore = WebCore::Initialize(config);
	
	// Create a new WebView instance with a certain width and height, using the
	// WebCore we just created
	webView = webCore->CreateWebView(webTexWidth, webTexHeight);
	
	// Load a certain URL into our WebView instance
	std::string str_address("http://www.google.com/");
	WebURL url(WebString::CreateFromUTF8(str_address.c_str(), str_address.length()));
	webView->LoadURL(url);
	
	webView->Focus();
}


void testApp::exit(){
    // Destroy our WebView instance
	webView->Destroy();
//	delete webCore;
}


void testApp::update(){
	webCore->Update();
    
    // Call our display func when the WebView needs rendering
	//if (webView->isDirty()) {
		BitmapSurface* surface = (BitmapSurface*)webView->surface();
		 
        //const Awesomium::RenderBuffer* renderBuffer = webView->rrender();
        if (surface) {
            webTex.loadData(surface->buffer(), webTexWidth, webTexHeight, GL_BGRA);
        }
    //}
}


void testApp::draw(){
    ofSetColor(255);

	if (isResizing == false) {
		//webTex.draw(0, 0);
	}


	webTex.draw(0, 0);
	
	if (webView->IsLoading()) {
        ofSetColor(0);
        ofDrawBitmapString("Loading...", 10, ofGetHeight()-20);
    }
	
	ofEnableAlphaBlending();
	ofSetColor(ofColor::black, 127);
	ofRect(0, 0, ofGetWindowWidth(), 30);
	ofDisableAlphaBlending();
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Press 'c' for Copy, 'p' for Paste", 50, 20);
}


void testApp::keyPressed(int key){
	switch (key) {
		case 'c':
			webView->Copy();
			break;
		case 'v':
			webView->Paste();
			break;
	}
}


void testApp::keyReleased(int key){

}


void testApp::mouseMoved(int x, int y ){
    webView->InjectMouseMove(x, y);
}


void testApp::mouseDragged(int x, int y, int button){
    webView->InjectMouseMove(x, y);
}


void testApp::mousePressed(int x, int y, int button){
	webView->InjectMouseDown(Awesomium::MouseButton::kMouseButton_Left);
}


void testApp::mouseReleased(int x, int y, int button){
	webView->InjectMouseUp(Awesomium::MouseButton::kMouseButton_Left);
}


void testApp::windowResized(int w, int h){

	isResizing = true;
	webTexWidth = w;
	webTexHeight = h;
	webTex.allocate(w, h, GL_RGBA);

	webView->Resize(w, h);
	webCore->Update();

}
