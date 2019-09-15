#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <chrono>
#include <cassert>
#include <cmath>
#include <SDL_ttf.h>
#include "gui.h"

/*
NOTE: This is slightly outdated; the idea is mostly the same but the names are different now
	Current Implementation Ideas:
	- A @GUI_Pane has the main graphical styling, is rectangular, and holds any # of displays and options
		- A @GUI_Display holds a variable, a name, and an icon (image), and tracks the variable while displaying it with a name and icon
		- A @GUI_Option is functionally identical to a @GUI_Display, but with the added bonus of being selectable in a menu and having an associated
		  action performed once selected. This will be implemented with function pointers (maybe?). It also needs to have a list of events and
		  GUI_Option pointers associated to them to show how a cursor would move from option to option.
	- @GUI_Option should publicly extend @GUI_Display in order to simplify methods in @GUI_Pane
	- It is worth noting that variables, text, and names may be ommited from all of these elements if desired (eg a simple @Option with only an
	  icon in it, or a @Display with no icon and only text and a variable)
	- Also, all items can have additional graphical elements added (eg a border, a background color change, etc) to style the GUI more
	- GUI elements should also be made so that they can disappear and/or reappear when needed and inside of functions (a simple call like
	  pane1->visibleAt(20, 35) and/or pane1->invisible() would suffice)
*/

/*
	How to implement in SDL:
	- Create an SDL_Surface to store the entire graphical contents of a GUI_Pane
	- Create SDL_Surfaces for each of the inner GUI elements which store their states
	- Use SDL_FillRect, IMG_Load and TTF_RenderText_Blended with SDL_BlitSurface to update each surface graphically
	- Blit the GUI_Displays and GUI_Options onto the GUI_Pane SDL_Surface (ideally in any order, since there should be no overlap)
	- Create a hardware-accellerated SDL_Texture of this new SDL_Surface using SDL_CreateTextureFromSurface
	- Using the window's renderer and SDL_RenderCopy, render the updated GUI texture to the screen using an SDL_Rect for formatting
	- Await another update request
*/

// Function pointer typedef to make life easier
typedef bool (*GUI_Handler)();

// Helper function to make a custom color
void GUI_SetColor(SDL_Color* c, int r, int g, int b, int a);

class GUI_Pane {
private:
	// SDL_Surface * screen -- This surface is a malleable form of the final GUI texture, and is the dst of blits from child @GUI_Display s
	SDL_Surface* screen;
	// SDL_Texture * display -- This texture is created by a call to @SDL_CreateTextureFromSurface on @screen and is later @SDL_RenderCopy ed
	SDL_Texture* display;
	// SDL_Rect pos -- This rectangle stores the position and dimensions of the final render on the window. As such, it uses the window's
	// coordinate system to be positioned.
	SDL_Rect pos;
	// SDL_Rect canvas -- This rectangle stores the position and dimensions of the useable space in the @GUI_Pane . While you may think this is
	// simply @pos, the border of the pane still needs to be factored in. This uses the coordinate system of @screen rather than the window's
	// coordinates. This also ends up becoming the new origin for child @GUI_Display s; rather than make it another blitted surface, it's faster
	// to use math to reposition everything before blitting.
	SDL_Rect canvas;
	// std::vector<GUI_Display*> fields -- This is an array of @GUI_Display s that this @GUI_Pane is responsible for.
	std::vector<GUI_Display*> fields;
	// int b -- integer pixel width of the border around the @GUI_Pane. Primarily used in calculating @canvas 's position.
	int b;
	// Self explanatory
	SDL_Color bkColor;
	// Self explanatory
	SDL_Color brColor;
	// See the same construct of GUI_Display
	SDL_Color h_bkColor;
	// See the same construct of GUI_Display
	SDL_Color h_brColor;


public:
	GUI_Pane();
	GUI_Pane(SDL_Rect pos, int b, SDL_Color backgroundColor, SDL_Color borderColor, SDL_Color h_backgroundColor, SDL_Color h_borderColor);
	~GUI_Pane();
	// This is the function that blits all GUI_Displays' &display fields onto this &screen field, renders this to this &display field, and 
	// render copies it.
	void reRenderGUI();
	// This function should be called every "tick" to make sure tracked fields by GUI_Displays are updated. Returns false if the GUI did not
	// rerender, and true if it did.
	bool updateGUI();
	// This function accepts a pointer to heap memory to a GUI_Display and adds it to the fields vector. The user has to allocate the memory 
	// initially, but the Pane will deallocate the memory by itself.
	// Note: DO NOT deallocate the pointer you pass, as it will cause memory leaks. 
	void addDisplay(GUI_Display* disp);
	// Drops the GUI_Display at the given index of the fields vector. It is deleted, and the memory is cleaned up.
	void dropDisplay(int index);
	// Pops the GUI_Display at the given index of the fields vector. This GUI_Display is returned to the user.
	GUI_Display* popDisplay(int index);
	// Returns the pointer of the Display at the given index of the fields vector. The Display is not deleted.
	GUI_Display* getDisplay(int index);

	// Accessors:

	int getBorderWidth();
	SDL_Color getBackgroundColor();
	SDL_Color getBorderColor();
	SDL_Color getHBackgroundColor();
	SDL_Color getHBorderColor();
	SDL_Rect getPos();

	// Mutators:

	void setBorderWidth(int ib);
	void setBackgroundColor(SDL_Color c);
	void setBorderColor(SDL_Color c);
	void setHBackgroundColor(SDL_Color c);
	void setHBorderColor(SDL_Color c);
	void setPos(SDL_Rect p);
	

};

// GUI_Display is an blueprint for an object stored in a parent @GUI_Pane, and is the primary means of displaying information on the GUI.
// It is the parent class of @GUI_Menu , @GUI_Pic , and @GUI_Desc . Most of its nontrivial public functions are pure virtuals.
class GUI_Display {
protected:
	// SDL_Surface * display -- This surface is a malleable form of the final display, and is the dst of blits from other surfaces. During
	// GUI rendering, this surface is blitted to @screen of the parent @GUI_Pane .
	SDL_Surface* display;
	// SDL_Rect pos -- This rectangle stores the position and dimensions of this display field on the parent @GUI_Pane . It uses the 'modified'
	// coordinate system of the parent pane ( see @canvas memeber of @GUI_Pane )
	SDL_Rect pos;
	// SDL_Rect canvas -- This rectangle stores the position and dimensions of the useable space in the @GUI_Display . While you may think this is
	// simply @pos, the border of the display still needs to be factored in. This uses the coordinate system of the parent @canvas.
	SDL_Rect canvas;
	// SDL_Surface * iconDisp -- This is the destination of any @IMG_Load calls when setting the display's icon. This is later blitted to @display
	SDL_Surface* iconDisp;
	// SDL_Surface * label -- This is the destination of any @TTF_RenderText_Blended calls for simple text, and is blitted to @display later.
	SDL_Surface* label;
	// SDL_Surface * varDisp -- This is the destination of any @TTF_RenderText_Blended calls for variables, and is blitted to @display later.
	SDL_Surface* varDisp;
	// int b -- integer pixel width of the border around the @GUI_Display. Primarily used in calculating @canvas 's position. Defaults to 0.
	int b;
	// char ** labelText -- This string poiner stores the address of the text to render to @label
	char** labelText;
	// char* labelTraceback -- This stores the last printed value of @labelText to check for updates to labelText.
	char* labelTraceback;
	// int * var -- This stores the address of the integer to track and display. (Note: variable tracking only works with integers, and will
	// only print integer values even if enum types are used. This could be improved in an update, but would take a bit of work.)
	int* var;
	// int varTraceback -- This stores the last printed value of @var to check for updates to var. If traceback != *var, then a display update is
	// needed.
	int varTraceback;
	// char ** imgPath -- This pointer stores the address to the path to the desired image to display
	char** imgPath;
	// char * imgPathTraceback -- This stores the last printed value of @imgPath to check for updates to imgPath. Note that both this and @iconDisp
	// must be used to determine if the image was updated.
	char* imgPathTraceback;
	SDL_Surface** icon;
	SDL_Surface* iconTraceback;
	// bool usingImgPath -- This keeps track of whether the last update to img was called via a new path pointer or a new surface pointer. 
	bool usingImgPath;
	// SDL_Color bkColor -- This color will be used as the background of the display. Default set to the color of the parent @GUI_Pane .
	SDL_Color bkColor;
	// SDL_Color h_bkColor -- This color will be used as the background of the display when selected. Default set to @bkColor .
	SDL_Color h_bkColor;
	// SDL_Color brColor -- This color will be used to draw the border around the display. Default set to black.
	SDL_Color brColor;
	// SDL_Color h_brColor -- This color will be used as the background of the border when selected. Default set to @brColor .
	SDL_Color h_brColor;
	SDL_Color fontColor;
	SDL_Color h_fontColor;
	// TTF_Font* font -- This is the font that all text on the display uses.
	TTF_Font* font;
	// GUI_Handler handler -- This is a pointer to the function to call when the @GUI_Display is selected by the user. Currently has a bool return
	// type that can be discarded if not necessary (ideally to signal whether the action was successful?)
	GUI_Handler handler;
	// bool autoupdate -- Controls whether traceback changes and manual tracked variable sets change which icon display to use. Defaults to false.
	bool autoupdate;
	// bool isUpdate -- When true, the parent pane will call the prepDisplay() function and rerender the GUI.
	bool isUpdate;
	

	// Loads an SDL_Surface to @iconDisp from @imgPath . 
	void loadImg();
	// Loads an SDL_Surface to @label using @labelText
	void loadLabel();
	// Loads an SDL_Surface to @varDisp using @var
	void loadVar();
	// Calculates the dimensions and position of canvas (call after an update to the border)
	void calculateCanvas();
	// Helper function to initialize certain fields
	void defaultFields();

public:
	// Constructor initializes all values to their defaults
	GUI_Display(SDL_Rect p, int ib, SDL_Color bkc, SDL_Color brc, SDL_Color fc, SDL_Color hbkc, SDL_Color hbrc, SDL_Color hfc, TTF_Font* f);
	GUI_Display(SDL_Rect p);
	// Destructor does what destructors do
	~GUI_Display();
	// This is the big function that blits all the surfaces in the correct order and positions to @display. Conveniently returns a pointer to
	// the new display for blitting, if desired.
	virtual SDL_Surface* prepDisplay() = 0;
	// This should only be called from the parent @GUI_Pane 's update() function. It checks to see if the tracked variable(s) is different than
	// when it was displayed last and, if so, calls prepDisplay(). Returns the resulting surface from prepDisplay() if called, or NULL otherwise.
	virtual SDL_Surface* updateVar() = 0;

	// Accessors:

	SDL_Rect getPos();
	int getPosX();
	int getPosY();
	int getPosW();
	int getPosH();
	int getBorderWidth();
	char** getLabelAddr();
	int* getVarAddr();
	char** getImgPathAddr();
	char* getLabel();
	int getVar();
	char* getImgPath();
	SDL_Color getBkColor();
	SDL_Color getBorderColor();
	SDL_Color getFontColor();
	SDL_Color getHBkColor();
	SDL_Color getHBorderColor();
	SDL_Color getHFontColor();
	SDL_Surface* getDisplay();
	SDL_Rect getCanvas();
	TTF_Font* getFont();
	int getCanvasW();
	int getCanvasH();
	GUI_Handler getHandler();
	bool getAutoUpdate();
	bool getIsUpdate();


	// Mutators:

	void setPos(SDL_Rect p);
	void setPosX(int x);
	void setPosY(int y);
	void setPosW(int w);
	void setPosH(int h);
	void setBorderWidth(int ib);
	// Used to change the pointer the display uses for label text. To change the label itself, modify the data at the pointer's address.
	// Note: Use space characters to change the text wrapping; in addition, keep the amount of text low to keep it from wrapping in @GUI_Menu s.
	void setLabel(char** text);
	// Used to change the pointer the display uses for var text. To change the var itself, modify the data at the pointer's address.
	void setVar(int* v);
	// Used to change the pointer the display uses for image paths. To change the path itself, modify the data at the pointer's address.
	// Additionally, use of this overload is discouraged. Please use the
	// void setImg(SDL_Surface** img) overload instead and load your assets beforehand.
	void setImg(char** path);
	// Used to change the pointer the display uses for images. To change the image itself, modify the data at the pointer's address.
	// Note; There may be a potential bug where the display won't recognize an update to the surface if you don't change the address of the
	// surface. In other words, to update the surface properly, change the address stored in your SDL_Surface* you addressed-of in the function
	// call, don't change the data it points to. Destroy the old surface and load a new one. This should prevent bugs.
	void setImg(SDL_Surface** img);
	void setBkColor(SDL_Color c);
	void setBorderColor(SDL_Color c);
	void setFontColor(SDL_Color c);
	void setHBkColor(SDL_Color c);
	void setHBorderColor(SDL_Color c);
	void setHFontColor(SDL_Color c);
	void setFont(TTF_Font* f);
	void setHandler(GUI_Handler h);
	void setAutoUpdate(bool t);
	void setUsingImgPath(bool t);
	void resetUpdate();
	

};

SDL_Rect GUI_Display::getPos() {return pos;}
int GUI_Display::getPosX() {return pos.x;}
int GUI_Display::getPosY() {return pos.y;}
int GUI_Display::getPosW() {return pos.w;}
int GUI_Display::getPosH() {return pos.h;}
int GUI_Display::getBorderWidth() {return b;}
char** GUI_Display::getLabelAddr() { return labelText; }
int* GUI_Display::getVarAddr() { return var; }
char** GUI_Display::getImgPathAddr() { return imgPath; }
char* GUI_Display::getLabel() { return *labelText; }
int GUI_Display::getVar() { return *var; }
char* GUI_Display::getImgPath() { return *imgPath; }
SDL_Color GUI_Display::getBkColor() { return bkColor; }
SDL_Color GUI_Display::getBorderColor() { return brColor; }
SDL_Color GUI_Display::getFontColor() { return fontColor; }
SDL_Color GUI_Display::getHBkColor() { return h_bkColor; }
SDL_Color GUI_Display::getHBorderColor() { return h_brColor; }
SDL_Color GUI_Display::getHFontColor() { return h_fontColor; }
SDL_Surface* GUI_Display::getDisplay() { return display; }
SDL_Rect GUI_Display::getCanvas() { return canvas; }
TTF_Font* GUI_Display::getFont() { return font; }
int GUI_Display::getCanvasW() { return canvas.w; }
int GUI_Display::getCanvasH() { return canvas.h; }
GUI_Handler GUI_Display::getHandler() { return handler; }
bool GUI_Display::getAutoUpdate() { return autoupdate; }
bool GUI_Display::getIsUpdate() { return isUpdate; }
void GUI_Display::setPos(SDL_Rect p) { pos = p; }
void GUI_Display::setPosX(int x) { pos.x = x; }
void GUI_Display::setPosY(int y) { pos.y = y; }
void GUI_Display::setPosW(int w) { pos.w = w; calculateCanvas(); }
void GUI_Display::setPosH(int h) { pos.h = h; calculateCanvas(); }
void GUI_Display::setBorderWidth(int ib) { b = ib; }
void GUI_Display::setLabel(char** text) { labelText = text; }
void GUI_Display::setVar(int* v) { var = v; }
void GUI_Display::setImg(char** path) { imgPath = path; loadImg(); }
void GUI_Display::setImg(SDL_Surface** img) { icon = img; if (autoupdate) usingImgPath = false; }
void GUI_Display::setBkColor(SDL_Color c) { bkColor = c; }
void GUI_Display::setBorderColor(SDL_Color c) { brColor = c; }
void GUI_Display::setFontColor(SDL_Color c) { fontColor = c; }
void GUI_Display::setHBkColor(SDL_Color c) { h_bkColor = c; }
void GUI_Display::setHBorderColor(SDL_Color c) { h_brColor = c; }
void GUI_Display::setHFontColor(SDL_Color c) { h_fontColor = c; }
void GUI_Display::setFont(TTF_Font* f) { font = f; }
void GUI_Display::setHandler(GUI_Handler h) { handler = h; }
void GUI_Display::setAutoUpdate(bool t) { autoupdate = t; }
void GUI_Display::setUsingImgPath(bool t) { if (!autoupdate) usingImgPath = t; }
void GUI_Display::resetUpdate() { isUpdate = false; }

void GUI_Display::loadImg() {
	if (iconDisp != NULL)
		SDL_FreeSurface(iconDisp);
	iconDisp = IMG_Load(*imgPath);
	if (autoupdate) usingImgPath = true;
}

void GUI_Display::loadLabel() {
	if (label != NULL)
		SDL_FreeSurface(label);
	label = TTF_RenderText_Blended(font, *labelText, fontColor);
}

void GUI_Display::loadVar() {
	if (varDisp != NULL)
		SDL_FreeSurface(varDisp);
	varDisp = TTF_RenderText_Blended(font, std::to_string(*var).c_str(), fontColor);
}

void GUI_Display::calculateCanvas() {
	canvas.x = b;
	canvas.y = b;
	canvas.w = pos.w - 2 * b;
	canvas.h = pos.h - 2 * b;
}

void GUI_SetColor(SDL_Color* c, int r, int g, int b, int a) {
	c->r = r; c->g = g; c->b = b; c->a = a;
}

void GUI_Display::defaultFields() {
	iconDisp = NULL; label = NULL; varDisp = NULL; labelText = NULL; labelTraceback = NULL; var = NULL; varTraceback = -1; imgPath = NULL; 
	imgPathTraceback = NULL; icon = NULL; iconTraceback = NULL;	usingImgPath = false; autoupdate = false; isUpdate = false;
}

GUI_Display::GUI_Display(SDL_Rect p, int ib, SDL_Color bkc, SDL_Color brc, SDL_Color fc, SDL_Color hbkc, SDL_Color hbrc, SDL_Color hfc, TTF_Font* f) {
	pos = p; b = ib; bkColor = bkc; brColor = brc; fontColor = fc; h_bkColor = hbkc; h_brColor = hbrc; h_fontColor = hfc; font = f;
	defaultFields();
	calculateCanvas();
}

GUI_Display::GUI_Display(SDL_Rect p) {
	pos = p; b = 0; GUI_SetColor(&bkColor,0,0,0,0); GUI_SetColor(&brColor, 0, 0, 0, 0); GUI_SetColor(&fontColor, 0, 0, 0, 0); GUI_SetColor(&h_bkColor, 0, 0, 0, 0); GUI_SetColor(&h_brColor, 0, 0, 0, 0); GUI_SetColor(&h_fontColor, 0, 0, 0, 0); font = NULL;
	defaultFields();
	calculateCanvas();
}

// Destructor does what destructors do
GUI_Display::~GUI_Display() {
	icon = NULL; iconTraceback = NULL; labelTraceback = NULL; varTraceback = NULL, imgPathTraceback = NULL; var = NULL; labelText = NULL; imgPath = NULL;
	SDL_FreeSurface(iconDisp); SDL_FreeSurface(label); SDL_FreeSurface(varDisp); SDL_FreeSurface(display);
}

// GUI_Menu is a @GUI_Display formatted with an image, a label, and an integer, all of which can change. Used primarily for menus as buttons.
class GUI_Menu : public GUI_Display {
protected:
	// int lKern -- This many pixels will separate the image and the label. Defaults to 10.
	int lKern;
	// int rKern -- This many pixels will separate the variable and the label. Defaults to 10.
	int rKern;
	// int xOffset -- Calculated and used internally; distance b/w @canvas 's left side and the image's right side to center the display.
	int xOffset;
	// int yOffset -- Calculated and used internally; distance b/w @canvas 's top side and the top of the tallest element to center the display.
	int yOffset;
public:
	GUI_Menu();
	~GUI_Menu();

	SDL_Surface* prepDisplay();
	SDL_Surface* updateVar();

	int getXOffset();
	int getYOffset();
	int getLeftKern();
	int getRightKern();

	void setLeftKern(int k);
	void setRightKern(int k);
};

// GUI_Desc is a @GUI_Display with only text in it. The padding can be set, and text is wrapped.
class GUI_Desc : public GUI_Display {
protected:
	// int padding -- This is the pixel distance between the border and the text. Defaults to 20.
	int padding;

public:
	GUI_Desc();
	~GUI_Desc();

	SDL_Surface* prepDisplay();
	SDL_Surface* updateVar();

	int getPadding();

	void setPadding(int p);

};

// A GUI_Pic is a GUI_Display that only shows a picture that fills the entire background of the display. The picture can update.
class GUI_Pic : public GUI_Display {
protected:

public:
	GUI_Pic(SDL_Rect p, int ib, SDL_Color bkc, SDL_Color brc, SDL_Color fc, SDL_Color hbkc, SDL_Color hbrc, SDL_Color hfc, TTF_Font* f);
	GUI_Pic(SDL_Rect p);
	~GUI_Pic();

	SDL_Surface* prepDisplay();
	SDL_Surface* updateVar();

	// When called, uses the current dimensions of the image surface in use and the value of b to resize pos so the blitted image retains its
	// original dimensions after blitting.
	void resizeToImage();

};

GUI_Pic::GUI_Pic(SDL_Rect p, int ib, SDL_Color bkc, SDL_Color brc, SDL_Color fc, SDL_Color hbkc, SDL_Color hbrc, SDL_Color hfc, TTF_Font* f) : GUI_Display(p, ib, bkc, brc, fc, hbkc, hbrc, hfc, f) {}
GUI_Pic::GUI_Pic(SDL_Rect p) : GUI_Display(p) {}
GUI_Pic::~GUI_Pic() {}

SDL_Surface* GUI_Pic::prepDisplay() {
	// Grab the correct image source depending on which image system is being used
	SDL_Surface* imgDisplay = usingImgPath ? iconDisp : *icon;
	// Clear the old contents of display, if any
	if (display != NULL)
		SDL_FreeSurface(display);
	// Create a new blank surface for display with dimensions like the pos Rect and with a 32bit color depth with default masks
	display = SDL_CreateRGBSurface(0, pos.w, pos.h, 32, 0, 0, 0, 0);
	// Makes display the border color
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, brColor.r, brColor.g, brColor.b));
	// Blits the image into the remaining space defined by canvas, leaving the border color behind it
	SDL_BlitScaled(imgDisplay, NULL, display, &canvas);
	// Return the prepared surface
	return display;
}

SDL_Surface* GUI_Pic::updateVar() {
	if (usingImgPath) {
		// Compare the values of the string path names, inverting it (returns 0 if they are equal), and return if no change
		if (!strcmp(*imgPath, imgPathTraceback))
			return NULL;
		imgPathTraceback = *imgPath;
	}
	else {
		// Compare the addresses stored in iconTraceback and addressed by icon and return if they are equal
		if (*icon == iconTraceback)
			return NULL;
		iconTraceback = *icon;
	}

	isUpdate = true;
	// Otherwise, we need to update the display
	return prepDisplay();

}

void GUI_Pic::resizeToImage() {
	// Grab the correct image source depending on which image system is being used
	SDL_Surface* imgDisplay = usingImgPath ? iconDisp : *icon;
	// Resize pos to the same size as the image surface
	pos.h = imgDisplay->h;
	pos.w = imgDisplay->w;
	// And then add the border width twice to each side
	pos.h += 2 * b;
	pos.w += 2 * b;

	// Finally, prep the display again
	isUpdate = true;
	prepDisplay();
}
