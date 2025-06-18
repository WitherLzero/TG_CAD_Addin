#include "stdafx.h"
#include "../Func/Func.h"

void Func::_drawAndModel()
{
	// user create a new document, we get this document
	PartDocumentPtr pPart = TGCADApp::GetApplication()->GetActiveDocument();

	// create a sketch
	SketchPtr pSketch = pPart->Sketches->Add();
	RefPlanePtr pRefplane = pPart->RefPlanes->Item(3);

	const int pCnt = 4;
	vector<ProfilePtr> profiles(pCnt);

	// 1.draw six lines
	profiles[0] = pSketch->Profiles->Add(pRefplane);
	Lines2dPtr pLines2d = profiles[0]->GetLines2d();
	const int lineCnt = 6;

	vector<pair<double, double>> vVertices;
	vVertices.push_back(std::make_pair(-0.02, 0));
	vVertices.push_back(std::make_pair(-0.03, 0.06));
	vVertices.push_back(std::make_pair(-0.03, 0.08));
	vVertices.push_back(std::make_pair(0.03, 0.08));
	vVertices.push_back(std::make_pair(0.03, 0.06));
	vVertices.push_back(std::make_pair(0.02, 0));

	vector<Line2dPtr> lines2d;
	for (int i = 0; i < lineCnt; ++i) {
		pair<double, double> vertex = vVertices[i];
		pair<double, double> vertexNext = vVertices[(i + 1) % lineCnt];
		lines2d.push_back(pLines2d->AddBy2Points(vertex.first, vertex.second,
			vertexNext.first, vertexNext.second));
	}

	// --- constraints ---
	Relations2dPtr pRelations2d = profiles[0]->GetRelations2d();
	for (int i = 0; i < lineCnt; ++i) {
		Line2dPtr pLine = lines2d[i];
		Line2dPtr pNextLine = lines2d[(i + 1) % lineCnt];
		pRelations2d->AddKeypoint(pLine, (int)TGConstants::KeypointIndexConstants::igLineEnd,
			pNextLine, (int)TGConstants::KeypointIndexConstants::igLineStart, true);
	}
	pRelations2d->AddKeypointFix(lines2d[0],
		TGConstants::KeypointIndexConstants::igLineStart);

	// handle extruded protrusion
	CComSafeArray<IDispatch*> psa(1);
	psa[0] = profiles[0];
	double distance = 0.05;
	ModelPtr pModel = pPart->GetModels()->AddFiniteExtrudedProtrusion(
		static_cast<long>(psa.GetCount()),
		psa.GetSafeArrayPtr(),
		FeaturePropertyConstants::igRight,
		distance
	);

	// 2.draw three circle
	const int circleCnt = 3;
	vector<Circles2dPtr> pCircles2d(circleCnt);
	for (int i = 1; i <= circleCnt; ++i) {
		profiles[i] = pSketch->Profiles->Add(pRefplane);
		pCircles2d[i - 1] = profiles[i]->GetCircles2d();
	}
	pCircles2d[0]->AddByCenterRadius(0, 0.015, 0.0075);
	pCircles2d[1]->AddByCenterRadius(-0.015, 0.07, 0.005);
	pCircles2d[2]->AddByCenterRadius(0.015, 0.07, 0.005);

	// check if profile is closed
	auto status = profiles[0]->End(ProfileValidationType::igProfileClosed);
	for (int i = 1; i < pCnt; ++i) {
		status = status & profiles[i]->End(ProfileValidationType::igProfileClosed);
	}
	for (int i = 1; i < pCnt; ++i) {
		pModel = pPart->GetModels()->Item(1)->GetExtrudedCutouts()->AddThroughAll(
			profiles[i],
			FeaturePropertyConstants::igLeft,
			FeaturePropertyConstants::igRight
		);
	}

	// save the part
	// 统一使用 _save 方法， 可以选择指定路径保存
	// 
	//wchar_t cwd[MAX_PATH] = { 0 };
	//if (GetCurrentDirectoryW(MAX_PATH, cwd) != 0)
	//{
	//	std::wstring saveDir = std::wstring(cwd) + L"\\saved";
	//	CreateDirectoryW(saveDir.c_str(), nullptr);
	//	std::wstring partPath = saveDir + L"\\model.par";
	//	pPart->SaveAs(
	//		_bstr_t(partPath.c_str()));
	//}
}


void Func::_createDraft()
{
	ApplicationPtr pApp = TGCADApp::GetApplication();

	// my part Path
	wchar_t filePath[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = L"Part Files (*.par)\0*.par\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	if (!GetOpenFileName(&ofn)) return;

	std::wstring partPath = std::wstring(filePath);

	// create a Draft Doc
	DraftDocumentPtr pDraft = pApp->GetDocuments()->Add(L"SolidEdge.DraftDocument");
	if (!pDraft) return;

	// get sheet
	SheetGroupsPtr   pGroups = pDraft->GetSheetGroups();
	SheetGroupPtr    pGroup  = pGroups->Item(1);
	SheetPtr         pSheet  = pGroup->GetSheets()->Item(1);

	// get View set
	DrawingViewsPtr  pViews  = pSheet->GetDrawingViews();

	// attach the Part Doc
	ModelLinksPtr    pModelLinks = pDraft->GetModelLinks();
	ModelLinkPtr     pModelLink = pModelLinks->Add(_bstr_t(partPath.c_str()));

	double scale = 1.0;
	double topX = 0.1, topY = 0.1;
	double frontX = 0.1, frontY = 0.2;

	// 俯视图
	pViews->AddPartView(
		pModelLink,
		ViewOrientationConstants::igTopView,
		scale,
		topX,
		topY,
		PartDrawingViewTypeConstants::sePartDesignedView
	);

	// 前视图
	pViews->AddPartView(
		pModelLink,
		ViewOrientationConstants::igFrontView,
		scale,
		frontX,
		frontY,
		PartDrawingViewTypeConstants::sePartDesignedView
	);
}

void Func::_save() {
	ApplicationPtr pApp = TGCADApp::GetApplication();

	// try get current Active Doc
	IDispatch* pDispDoc = pApp->GetActiveDocument();

	if (!pDispDoc) {
		AfxMessageBox(L"NOT ACTIVE DOC");
		return;
	}

	// if PartDoc, call the part Save func
	PartDocumentPtr pPart;
	HRESULT hr = pDispDoc->QueryInterface(__uuidof(PartDocument), (void**)&pPart);
	if (SUCCEEDED(hr) && pPart) {
		pPart->Save();
		pDispDoc->Release();
		return;
	}

	// if draftDoc, call the draft Save func
	TGDraft::DraftDocumentPtr pDraft;
	hr = pDispDoc->QueryInterface(__uuidof(DraftDocument), (void**)&pDraft);
	if (SUCCEEDED(hr) && pDraft) {

		pDraft->Save();
		pDispDoc->Release();
		return;
	}

	pDispDoc->Release();

	AfxMessageBox(L"Save successfully");
}

void Func::DrawCircle()
{
	// get application
	ApplicationPtr application = TGCADApp::GetApplication();

	// get PartDocumentPtr
	TGPart::PartDocumentPtr pPart = application->GetDocuments()->Add("SolidEdge.PartDocument");

	// new sketch
	SketchPtr pSketch = pPart->Sketches->Add();

	// ref Plane
	RefPlanePtr pRefPlane = pPart->RefPlanes->Item(1);

	// get Profile
	ProfilePtr pFile = pSketch->GetProfiles()->Add(pRefPlane);

	// draw circle
	Circle2dPtr pCircle = pFile->GetCircles2d()->AddByCenterRadius(-0.5, -0.5, 0.2);

}

void Func::DrawSnapRing()
{
	// a new part document
	PartDocumentPtr pPart = TGCADApp::GetApplication()->GetDocuments()
		->Add("SolidEdge.PartDocument");
	// sketch
	SketchPtr pSketch = pPart->Sketches->Add();
	// get ref Plane
	RefPlanePtr pRefPlane = pPart->RefPlanes->Item(3);
	// get profile
	ProfilePtr pProfile = pSketch->Profiles->Add(pRefPlane);

	// draw four lines
	Lines2dPtr pLines = pProfile->GetLines2d();
	const int len = 4;

	vector<pair<double, double>> vVerteis;
	vVerteis.push_back(std::make_pair(-0.001, 0.014));
	vVerteis.push_back(std::make_pair(-0.001, 0.016));
	vVerteis.push_back(std::make_pair(0.001, 0.016));
	vVerteis.push_back(std::make_pair(0.001, 0.014));

	// 1.draw line
	vector<Line2dPtr> lines2d;
	for (int i = 0; i < len; ++i) {
		pair<double, double> vertex = vVerteis[i];
		pair<double, double> vertexNext = vVerteis[(i + 1) % len];
		lines2d.push_back(pLines->AddBy2Points(vertex.first, vertex.second,
			vertexNext.first, vertexNext.second));

	}

	//2.constraint_connection
	Relations2dPtr pRelations2d = pProfile->GetRelations2d();
	for (int i = 0; i < len; ++i) {
		TGFrameworkSupport::Line2dPtr pLine = lines2d[i];
		TGFrameworkSupport::Line2dPtr pNextLine = lines2d[(i + 1) % len];
		pRelations2d->AddKeypoint(pLine, (int)TGConstants::KeypointIndexConstants::igLineEnd,
			pNextLine, (int)TGConstants::KeypointIndexConstants::igLineStart, true);
	}

	//3.constraint_Horizontal&Vertical
	pRelations2d->AddVertical(lines2d[0]);
	pRelations2d->AddHorizontal(lines2d[1]);
	pRelations2d->AddVertical(lines2d[2]);
	pRelations2d->AddHorizontal(lines2d[3]);

	//4.constraint_dimensions
	DimensionsPtr pDims = pProfile->GetDimensions();
	DimensionPtr pDim;
	for (int i = 0; i < len; ++i) {
		pDim = pDims->AddLength(lines2d[i]);
		pDim->PutConstraint(true);
	}

	//5.constraint_fixed
	pRelations2d->AddKeypointFix(lines2d[0],
		TGConstants::KeypointIndexConstants::igLineStart);

	//
	auto status = pProfile->End(ProfileValidationType::igProfileClosed);

}
