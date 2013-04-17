#include "testApp.h"
#include "clipBoardWin.h"
#include <Awesomium\BitmapSurface.h>
#include "ScriptEngineBridger.h"

using namespace Awesomium;

void testApp::setup(){

	ScriptEngineBridger::instance().testEngine();
	

	trackUserText = false;
	isResizing = false;
	webTexWidth = 300; //ofGetWindowWidth()/2;
	webTexHeight = ofGetWindowHeight() - 100;
    webTex.allocate(webTexWidth, webTexHeight, GL_RGBA); 

	setGUI();

	

	//_img.loadImage("nerd_me.png");
    // Disable scrollbars via the WebCoreConfig
	Awesomium::WebConfig config;
    //config.setCustomCSS("::-webkit-scrollbar { display: none; }");
    
	// Create our WebCore singleton with the default options
	webCore = WebCore::Initialize(config);
	
	// Create a new WebView instance with a certain width and height, using the
	// WebCore we just created
	webView = webCore->CreateWebView(webTexWidth, webTexHeight);
	
	// Load a certain URL into our WebView instance
	std::string str_address("http://www.wikipedia.com/");
	WebURL url(WebString::CreateFromUTF8(str_address.c_str(), str_address.length()));
	webView->LoadURL(url);
	
	webView->Focus();
	oldMouseX = mouseX = 0;
	oldMouseX = mouseY = 0;

	isLoadingComplete = false;
}

void testApp::setGUI() {

	float dim = 16; 


	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; //length*3+xInit*3+6
	gui4 = new ofxUIScrollableCanvas(0, 0, 350, ofGetHeight());     
	//gui4 = new ofxUICanvas(0, 0, 350, ofGetHeight());     
	gui4->setSnapping(true);
	gui4->setColorFill(ofColor::aquamarine);
    gui4->addWidgetDown(new ofxUILabel("PANEL 4: SCROLLABLE", OFX_UI_FONT_LARGE)); 	
    gui4->addSpacer(length-xInit, 2);
	webTexture = new ofxTexturedUI(webTexWidth, webTexHeight, NULL, "test");

	gui4->addWidgetDown(webTexture);

	std::cout<<"w="<<gui4->getRect()->getWidth()<<" h="<<gui4->getRect()->getHeight()<<std::endl;
	std::cout<<"x="<<webTexture->getRect()->getX()<<" y="<<webTexture->getRect()->getY()<<" w="<<webTexture->getRect()->getWidth()<<" h="<<webTexture->getRect()->getHeight()<<std::endl;


 //   
    //gui4->addSpacer(length-xInit, 2);

    //gui4->addWidgetDown(new ofxUILabel("BILABEL SLIDER", OFX_UI_FONT_MEDIUM)); 				
    //gui4->addWidgetDown(new ofxUIBiLabelSlider(length-xInit, 0, 100, 50, "BILABEL", "HOT", "COLD", OFX_UI_FONT_MEDIUM));

 //   
 //   
	ofAddListener(gui4->newGUIEvent,this,&testApp::guiEvent);
}


void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "BACKGROUND VALUE")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        ofBackground(slider->getScaledValue());
    }
    else if(e.widget->getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   


    }
}

void testApp::exit(){
    // Destroy our WebView instance
	webView->Destroy();
	//delete webTexture;
//	delete webCore;
}


void testApp::update(){
	webCore->Update();
    
    // Call our display func when the WebView needs rendering
	//if (webView->isDirty()) {
		BitmapSurface* surface = (BitmapSurface*)webView->surface();
		
        //const Awesomium::RenderBuffer* renderBuffer = webView->rrender();
		if (surface && surface->is_dirty()) {
			//std::cout<<"w="<<surface->width()<<" w2="<<webTexWidth<<" h="<<surface->height()<<std::endl;
            webTex.loadData(surface->buffer(), webTexWidth, webTexHeight, GL_BGRA); 			
			if(isLoadingComplete) {
				webTexture->setTexture(&webTex);
				isLoadingComplete = false;
			}
			
        }
    //}
}


void testApp::draw(){
    ofSetColor(255);

	if (isResizing == false) {
		//webTex.draw(0, 0);
	}


	//webTex.draw(0, 0, webTexWidth, webTexHeight);
	
	
	//_img.draw(webTexWidth+10, 0);
	if (webView->IsLoading()) {
        ofSetColor(0);
        ofDrawBitmapString("Loading...", 10, ofGetHeight()-20);
		isLoadingComplete = false;
    } else {
		isLoadingComplete = true;
	}
	
	
	ofEnableAlphaBlending();
	ofSetColor(ofColor::black, 127);
	ofRect(0, 0, ofGetWindowWidth(), 30);
	ofDisableAlphaBlending();
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Press 'c' for Copy, 'p' for Paste", 50, 20);

	if(trackUserText) {
		ofSetColor(ofColor::brown);

		_line.draw();
	
		//ofLine(oldMouseX, oldMouseY, mouseX, mouseY);

		//oldMouseX = mouseX;
		//oldMouseY = mouseY;
	}
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
	mouseX = x;
	mouseY = y;
	_line.addVertex(x,y);
}


void testApp::mouseDragged(int x, int y, int button){
    webView->InjectMouseMove(x, y);
}


void testApp::mousePressed(int x, int y, int button){
	webView->InjectMouseDown(Awesomium::MouseButton::kMouseButton_Left);
	trackUserText = true;
}


void testApp::mouseReleased(int x, int y, int button){
	webView->InjectMouseUp(Awesomium::MouseButton::kMouseButton_Left);
	_line.clear();
	webView->Copy();
	std::string data = getClipBoardString();
	std::cout<<"clipboard has :"<<data<<std::endl;
}


void testApp::windowResized(int w, int h){

	isResizing = true;
	//webTexWidth = w;
	//webTexHeight = h;
	//webTex.allocate(w, h, GL_RGBA);

	//webView->Resize(w, h);
	//webCore->Update();

}

void testApp::gotMessage(ofMessage msg){

}



//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
