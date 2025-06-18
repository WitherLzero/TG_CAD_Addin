#pragma once
#include "TGCADApp.h"
#include "resource.h"
#include "TGCAD_i.h"

using std::vector;
using std::pair;
using namespace TGDraft;

namespace Func
{

	// a test function
	void DrawCircle();

	// prac : draw SnapRing
	void DrawSnapRing();

	/* -------ASSIGNMENT------- */
	//1. draw sketch and create model
	void _drawAndModel();

	//2. create draft
	void _createDraft();

	//2. Save Document Func
	void _save();

}