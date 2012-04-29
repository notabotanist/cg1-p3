// 
// File: stereo.cpp 
// 
// @author matthew: TODO_AUTHOR_FULL_NAME_
// 
// Version: 
// $Id$ 
// 
// Revisions: 
// $Log$ 
// 
// //////////////////////////////////////////////////////////////////// 

// include files, system headers first
#include <iostream>         // system header include for I/O

#include "stereo.h"          // local header include

/// namespace TODO_OPTIONAL_ is optional
// namespace TODO_OPTIONAL_ {

/// ctor TODO_BRIEF_DOCS_
StereoViewport::StereoViewport() {
}

/// dtor TODO_BRIEF_DOCS_
StereoViewport::~StereoViewport() {

}

/// rendering callback
void StereoViewport::display() {
	// setup viewport 1
	drawScene();
	// setup viewport 2
	drawScene();
}

// } // end namespace TODO_OPTIONAL_

// (main function is NEVER in a namespace)
/////////////////////////// main // TODO_ // DELETE section if not needed

///
/// main function TODO_DOCS_
/// @author matthew: TODO_AUTHOR_FULL_NAME_
///
/// @param argc  number of command line arguments, including program name
/// @param argv  supplied command line arguments, including program name
/// @returns errorCode  the error Code; 0 if no error
///
int main( int argc, char* argv[] ) {

}

