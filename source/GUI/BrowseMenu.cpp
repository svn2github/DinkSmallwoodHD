#include "PlatformPrecomp.h"
#include "BrowseMenu.h"
#include "MainMenu.h"
#include "DMODInstallMenu.h"
#include "GameMenu.h"
#include "Entity/EntityUtils.h"
#include "dink/dink.h"
#include "PopUpMenu.h"
#include "util/TextScanner.h"
#include "EnterURLMenu.h"
#include "Renderer/SoftSurface.h"
#include "QuickTipMenu.h"
#include "DMODMenu.h"
#include "Network/NetHTTP.h"
#include "Entity/HTTPComponent.h"


struct DMODEntry
{
	string m_name;
	string m_url;
	string m_author;
	float m_size;
	float m_rating;
	string m_description;
	uint32 m_date;
	float m_version;
};

void BrowseMenuAddScrollContent(Entity *pParent, TextScanner &t);
Entity * ShowScoreMessage(Entity *pMenu, string msg);

void BrowseMenuOnSelect(VariantList *pVList) //0=vec2 point of click, 1=entity sent from
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();
	LogMsg("Clicked %s entity at %s", pEntClicked->GetName().c_str(),pVList->m_variant[1].Print().c_str());
	Entity *pMenu = GetEntityRoot()->GetEntityByName("BrowseMenu");

	//LogMsg("Clicked %s entity at %s", pEntClicked->GetName().c_str(),pVList->m_variant[0].Print().c_str());

	if (pEntClicked->GetName() == "Back")
	{
		SlideScreen(pEntClicked->GetParent(), false);
		GetMessageManager()->CallEntityFunction(pEntClicked->GetParent(), 500, "OnDelete", NULL);
		DMODMenuCreate(pEntClicked->GetParent()->GetParent(), true);
		return;
	}

	//they must have clicked on a DMOD if they got this far
	if (pEntClicked->GetName() == "install")
	{
		//save position of the scroll bar first
		EntityComponent *pScrollerComp = pMenu->GetEntityByName("scroll")->GetComponentByName("Scroll");
		//GetApp()->GetVar("DMODProgress2d")->Set(pScrollerComp->GetVar("progress2d")->GetVector2());

		string dmodurl = pEntClicked->GetParent()->GetVar("dmodurl")->GetString();
		string dmodName = pEntClicked->GetParent()->GetVar("dmodtitle")->GetString();

		SendFakeInputMessageToEntity(GetEntityRoot(), MESSAGE_TYPE_GUI_CLICK_END, pVList->m_variant[0].GetVector2()); //otherwise the menu may never get the touch release message
	
		DisableAllButtonsEntity(pMenu);
		SlideScreen(pMenu, false);
		GetMessageManager()->CallEntityFunction(pMenu, 500, "OnDelete", NULL);
		DMODInstallMenuCreate(pEntClicked->GetParent()->GetParent()->GetParent()->GetParent()->GetParent(), dmodurl, GetDMODRootPath() , "", true, dmodName);

	}

	/*
	if (pEntClicked->GetName() == "rtsoft")
	{
	PopUpCreate(pEntClicked->GetParent()->GetParent()->GetParent(), "Leave the game and visit `wrtsoft.com``?", "http://www.rtsoft.com/iphone",
	"cancel", "`wCancel", "url", "`wLaunch", true);
	return;
	}
	*/	

	GetEntityRoot()->PrintTreeAsText(); //useful for debugging
}


string VersionToString(float v)
{
	char tmp[32];
	sprintf(tmp, "%.2f", v);
	if (tmp[3] == '0')
	{
		//cut off this, not needed
		tmp[3] = 0;
	}

	return string(tmp);

}
void AddEntryBar(Entity *pParent, float &x, float &y, DMODEntry &s, int count)
{
	Entity *pBG = CreateOverlayEntity(pParent, s.m_name, ReplaceWithLargeInFileName("interface/iphone/browse_dmod_bar.rttex"),x, y);

	y += pBG->GetVar("size2d")->GetVector2().y;

	pBG->GetVar("dmodurl")->Set(s.m_url); //save for later
	pBG->GetVar("dmodtitle")->Set(s.m_name); //save for later
	//title
	char stTemp[512];
	sprintf(stTemp, "`6%s ``V%s`6%s - ``%.2f mb``", s.m_name.c_str(), VersionToString(s.m_version).c_str(), s.m_author.c_str(), s.m_size); 
	Entity *pTitle = CreateTextLabelEntity(pBG, "title", iPhoneMapX2X( 16) ,iPhoneMapY2X( 13), stTemp);
	Entity *pDescription = CreateTextBoxEntity(pBG, "descrip", iPhoneMap2X(16, 34), iPhoneMap2X(425, 54), "`6"+s.m_description); 

	//Entity *pIcon = CreateButtonHotspot(pBG, "icon_hotspot", GetDMODBarIconOffset(), GetDMODBarIconSize(), Button2DComponent::BUTTON_STYLE_CLICK_ON_TOUCH_IGNORE_DRAGGING);
	//SetTouchPaddingEntity(pIcon, CL_Rectf(0,iPhoneMapY2X(5),0,iPhoneMapY2X(5)));
	//pIcon->GetFunction("OnButtonSelected")->sig_function.connect(&BrowseMenuOnSelect);

	//processing the icon image might be slow, lets do it a bit later, sequencing the timing by using the y, which should be going up
	
	//the delete icon part
	{
		CL_Vec2f iconPos = iPhoneMap2X(379,10);
		//CL_Vec2f iconSize = iPhoneMap2X(27, 27);
		Entity *pIcon = CreateOverlayButtonEntity(pBG, "install", ReplaceWithLargeInFileName("interface/iphone/browse_install.rttex"), iconPos.x, iconPos.y);
		SetButtonStyleEntity(pIcon,  Button2DComponent::BUTTON_STYLE_CLICK_ON_TOUCH_IGNORE_DRAGGING);
		SetTouchPaddingEntity(pIcon, CL_Rectf(0,0,0,0));
		pIcon->GetFunction("OnButtonSelected")->sig_function.connect(&BrowseMenuOnSelect);
	}

	//add animation effect
	ZoomToPositionFromThisOffsetEntity(pBG, CL_Vec2f(GetScreenSizeXf(), 0), 500, INTERPOLATE_EASE_TO, 10);
}


void BrowseMenuAddScrollContent(Entity *pParent, TextScanner &t)
{
	pParent = pParent->GetEntityByName("scroll_child");

	pParent->RemoveAllEntities();
	float x = iPhoneMapX(5);
	float y = 0;

	//Entity *pEnt;

	int dmodsAdded = 0;

	string msg = t.GetMultipleLineStrings("msg", "|");
	vector<string> p = StringTokenize(msg, "|");

	if (p.size() == 2 && p[1].length() > 1)
	{
		
		StringReplace("<cr>", "\n", p[1]);
		//add a message we just downloaded
		CL_Vec2f vTextBoxPos(x+iPhoneMapX(5),y);
		CL_Vec2f vTextBounds(iPhoneMapX(434), iPhoneMapY(200));
		Entity *pEnt = CreateTextBoxEntity(pParent, "", vTextBoxPos, vTextBounds, p[1]);
		y += pEnt->GetVar("size2d")->GetVector2().y;
		y += iPhoneMapY(5);

	}

	string line;
	while ( string(line = t.GetMultipleLineStrings("add", "|")).length() > 0)
	{
		//LogMsg(line.c_str());
		vector<string> p = StringTokenize(line, "|");

		if (p.size() < 7)
		{
			continue;
		}
		DMODEntry s;
		s.m_name = p[1];
		s.m_url = p[2];
		s.m_author = p[3];
		s.m_size = atof(p[4].c_str());
		s.m_rating = atof(p[5].c_str());
		s.m_description = p[6];
		s.m_version = atof(p[7].c_str());

//		s.m_date = atol(p[5].c_str());
		
		//m_onlineScores.push_back(s);
		AddEntryBar(pParent, x, y,s, dmodsAdded);
		dmodsAdded++;
		y += iPhoneMapY(5);

	}


    
    VariantList vList(pParent->GetParent());
	ResizeScrollBounds(&vList);
	DisableHorizontalScrolling(pParent->GetParent());

}



void OnDownloadError(VariantList *pVList)
{
	NetHTTP::eError e = (NetHTTP::eError)pVList->m_variant[1].GetUINT32();

	string msg = "`4Unable to connect.  Try later. ("+toString(e)+")";
	if (e == NetHTTP::ERROR_COMMUNICATION_TIMEOUT)
	{
		msg = "`4Connection timed out. Try Later.";
	}

	ShowScoreMessage(pVList->m_variant[0].GetComponent()->GetParent(), msg);
}


Entity * ShowScoreMessage(Entity *pMenu, string msg)
{
	Entity *pInfo = pMenu->GetEntityByName("Info");
	if (pInfo)
	{
		pInfo->GetComponentByName("TextRender")->GetVar("text")->Set(msg);
		pInfo->RemoveComponentByName("Typer"); // a thing that types stuff
	} else
	{
		pInfo = CreateTextLabelEntity(pMenu, "Info", iPhoneMapX(130), iPhoneMapY(220), msg);
	}

	return pInfo;
}


void OnDownloadHTTPFinish(VariantList *pVList)
{
	Entity *pMenu = pVList->m_variant[0].GetComponent()->GetParent();

	TextScanner t((char*)pVList->m_variant[1].GetString().c_str());
	string line;

	//	ShowScoreMessage(pMenu, t.GetParmString("msg",1));
	ShowScoreMessage(pMenu, "");
	//GetApp()->GetVar("score_msg")->Set(t.GetParmString("msg",1));

	//GetHighScoreManager()->SetupOnlineScores(t);
	//GetApp()->GetVar("cur_score")->Set(uint32(0));  //reset score drawing
	//ScoresAddStuffToScroll(NULL);
	BrowseMenuAddScrollContent(pMenu, t);

	//	AddHighScores(pMenu, -1);
}


void DownloadDMODList(Entity *pMenu)
{
	pMenu->RemoveComponentByName("HTTP"); //just in case it already exists

	//get the internet stuff going
	EntityComponent *pComp = pMenu->AddComponent(new HTTPComponent);

	VariantList vPostData;

	vPostData.m_variant[0].Set("version");
	vPostData.m_variant[1].Set(toString(GetApp()->GetVersion()));
	pComp->GetFunction("AddPostData")->sig_function(&vPostData);

	vPostData.m_variant[0].Set("build");
	vPostData.m_variant[1].Set(toString(GetApp()->GetBuild()));
	pComp->GetFunction("AddPostData")->sig_function(&vPostData);

	vPostData.m_variant[0].Set("platform");
	vPostData.m_variant[1].Set(toString(GetEmulatedPlatformID()));
	pComp->GetFunction("AddPostData")->sig_function(&vPostData);

	VariantList v;

	string url;
	uint32 port;
	GetApp()->GetServerInfo(url, port);

	v.m_variant[0].Set(url);
	v.m_variant[1].Set(port);
	v.m_variant[2].Set("dink/getaddons.php");
	pComp->GetFunction("Init")->sig_function(&v);
	pComp->GetFunction("OnError")->sig_function.connect(&OnDownloadError);
	pComp->GetFunction("OnFinish")->sig_function.connect(&OnDownloadHTTPFinish);

	Entity *pEnt = ShowScoreMessage(pMenu, "`6");
	EntityComponent *pTyper = pEnt->AddComponent(new TyperComponent);
	pTyper->GetVar("text")->Set("Downloading add-on list...");
	pTyper->GetVar("speedMS")->Set(uint32(50));
	//KillScores();

}

void BrowseOnPostIntroTransition(VariantList *pVList)
{

	Entity *pBG = pVList->Get(0).GetEntity();
	
	DownloadDMODList(pBG);

	//CreateQuickTipFirstTimeOnly(pBG, "interface/iphone/quicktip_dmod.rttex", false);
}

Entity * BrowseMenuCreate( Entity *pParentEnt )
{
	//GetMessageManager()->SendGame(MESSAGE_TYPE_PLAY_MUSIC, "audio/title.mp3", 200);
	GetBaseApp()->ClearError();

	Entity *pBG = NULL;

	if (IsLargeScreen())
	{
		pBG =  CreateOverlayEntity(pParentEnt, "BrowseMenu", ReplaceWithDeviceNameInFileName("interface/iphone/bkgd_stone.rttex"), 0,0);

	} else
	{
		//pBG = CreateOverlayEntity(pParentEnt, "BrowseMenu", "interface/iphone/dmod_bg.rttex", 0,0);
		pBG = CreateOverlayEntity(pParentEnt, "BrowseMenu", ReplaceWithDeviceNameInFileName("interface/iphone/bkgd_stone.rttex"), 0,0);
	}

	pBG->SetName("BrowseMenu");
	AddFocusIfNeeded(pBG, true, 500);
	pBG->AddComponent(new FocusRenderComponent);

	CL_Vec2f vTextAreaPos = iPhoneMap(2,10);
	float offsetFromBottom = iPhoneMapY(42);
	float offsetFromRight = iPhoneMapY(0);

	CL_Vec2f vTextAreaBounds = (GetScreenSize()- CL_Vec2f(offsetFromRight,offsetFromBottom))-vTextAreaPos;
	Entity *pScroll = pBG->AddEntity(new Entity("scroll"));
	pScroll->GetVar("pos2d")->Set(vTextAreaPos);
	pScroll->GetVar("size2d")->Set(vTextAreaBounds);
	pScroll->AddComponent(new TouchHandlerComponent);

	/*
	Entity *pLabel = CreateTextLabelEntity(pBG, "scanning", GetScreenSizeXf()/2, GetScreenSizeYf()/2, "Updating add-on browse list...");
	SetAlignmentEntity(pLabel, ALIGNMENT_CENTER);
	FadeOutAndKillEntity(pLabel, true, 300, 501);

	*/

	EntityComponent *pFilter = pScroll->AddComponent(new FilterInputComponent);

	EntityComponent *pScrollComp = pScroll->AddComponent(new ScrollComponent);
	EntityComponent *pScrollBarComp = pScroll->AddComponent(new ScrollBarRenderComponent); 	//also let's add a visual way to see the scroller position
	//pScroll->GetVar("color")->Set(MAKE_RGBA(61,155, 193, 255)); 
	Entity *pScrollChild = pScroll->AddEntity(new Entity("scroll_child"));
	pScrollComp->GetVar("fingerTracking")->Set(uint32(1));

	//EntityComponent *pClip = pScroll->AddComponent(new RenderClipComponent);
	//pClip->GetVar("clipMode")->Set(uint32(RenderClipComponent::CLIP_MODE_BOTTOM));

	Entity *pOverlay = CreateOverlayEntity(pBG, "", ReplaceWithDeviceNameInFileName("interface/iphone/bg_stone_overlay.rttex"), 0, GetScreenSizeYf()); 
	SetAlignmentEntity(pOverlay, ALIGNMENT_DOWN_LEFT);


	//	ZoomFromPositionEntity(pBG, CL_Vec2f(0, -GetScreenSizeYf()), 500);
	//the continue button
	Entity *pEnt;

	//pEnt = CreateOverlayRectEntity(pBG, CL_Rectf(0, GetScreenSizeYf()-offsetFromBottom, GetScreenSizeXf(), 320), MAKE_RGBA(0,0,0,100));

	eFont fontID = FONT_SMALL;

	pEnt = CreateTextButtonEntity(pBG, "Back", iPhoneMapX(25), iPhoneMapY(BACK_BUTTON_Y), "Back", false);
	pEnt->GetFunction("OnButtonSelected")->sig_function.connect(&BrowseMenuOnSelect);
	SetupTextEntity(pEnt, fontID);
	AddHotKeyToButton(pEnt, VIRTUAL_KEY_BACK);

	SlideScreen(pBG, true, 500);
	pBG->GetFunction("OnPostIntroTransition")->sig_function.connect(&BrowseOnPostIntroTransition);
	VariantList vList(pBG, string(""));
    GetMessageManager()->CallEntityFunction(pBG, 500, "OnPostIntroTransition", &vList); 

	return pBG;
}