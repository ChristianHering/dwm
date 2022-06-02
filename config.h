/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Inconsolata-g:size=13", "NotoColorEmoji:pixelsize=13:antialias=true:autohint=true" };
static const char dmenufont[]       = "Inconsolata-g:size=13";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[Hg]",     horizgrid }, // first entry is default
	{ "[T]",      tile }, // default tiling mode
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_d,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_p,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_p,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_p,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_p,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static char *statuscmds[] = {
	{ "wget http://localhost:1058/eventSection/0/eventButton/$BUTTON", 1 },
	{ "wget http://localhost:1058/eventSection/1/eventButton/$BUTTON", 2 },
	{ "wget http://localhost:1058/eventSection/2/eventButton/$BUTTON", 3 },
	{ "wget http://localhost:1058/eventSection/3/eventButton/$BUTTON", 4 },
	{ "wget http://localhost:1058/eventSection/4/eventButton/$BUTTON", 5 },
	{ "wget http://localhost:1058/eventSection/5/eventButton/$BUTTON", 6 },
	{ "wget http://localhost:1058/eventSection/6/eventButton/$BUTTON", 7 },
	{ "wget http://localhost:1058/eventSection/7/eventButton/$BUTTON", 8 },
	{ "wget http://localhost:1058/eventSection/8/eventButton/$BUTTON", 9 },
	{ "wget http://localhost:1058/eventSection/9/eventButton/$BUTTON", 10 },
};
static char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

static Key keys[] = {
//  modifier                        key        function        argument

	//stacker patch
	STACKKEYS(MODKEY|ShiftMask,                focus) //TODO: Moves Window Up In Focus, Changes Context To Fullscreen If Master
	STACKKEYS(MODKEY,                          push) //TODO: Moves Window Down In Focus, Hides Window Behind New If Fullscreen

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	//System Keybindings
	{ MODKEY,                       XK_q,      killclient,	   {0} }, //Kills The Window In Focus
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, //Forcefully Exits DWM
	{ MODKEY,                       XK_r,      spawn,          SHCMD("dmenu_run") }, //Launch "run" (dMenu)
	{ MODKEY,                       XK_space,  zoom,           {0} }, //Makes The Focused Window The Master Window
	{ MODKEY,                       XK_Left,   tagmon,         {.i = +1 } }, //Send Window In Focus To The Left
	{ MODKEY,                       XK_Right,  tagmon,         {.i = -1 } }, //Send Window In Focus To The Right
	{ MODKEY|ShiftMask,             XK_Left,   focusmon,       {.i = +1 } }, //Moves Focus To Left Display
	{ MODKEY|ShiftMask,             XK_Right,  focusmon,       {.i = -1 } }, //Moves Focus To Right Display
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   setmfact,       {.f = -0.01} }, //Moves The Window Devider To The Left
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  setmfact,       {.f = +0.01} }, //Moves The Window Devider To The Right
	{ MODKEY|Mod1Mask,              XK_f,      togglefloating, {0} }, //Toggles Floating For The Focused Window
	{ MODKEY,                       XK_p,      togglebar,      {0} }, //Toggles DWM Status Bar
//	{ MODKEY,                       XK_space,  setlayout,      {0} }, //Change To The Priviously Used Layout
//	{ MODKEY,                       XK_f,      setfullscreen,  {0} }, //Toggle Fullscreen Mode
//	{ MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("") }, //Copy
//	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("") }, //Cut
//	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("") }, //Paste
//	{ MODKEY,                       XK_Tab,    {0},            {0} }, //List Active Programs in Tag Tab
//	{ MODKEY,                       XK_h,      {0},            {0} }, //Shows Desktop/Hides All Applications

	//Audio
	{ MODKEY,                       XK_m,      spawn,          SHCMD("pamixer -t") }, //Mute Audio
	{ MODKEY,                       XK_period, spawn,          SHCMD("pamixer --allow-boost -i 3") }, //Increase Audio Volume
	{ MODKEY,                       XK_comma,  spawn,          SHCMD("pamixer --allow-boost -d 3") }, //Decrease Audio Volume

	//Screen Capture
	{ MODKEY,                       XK_Print,  spawn,          SHCMD("flameshot gui") }, //Launch FlameShot (ScreenShot tool)
	{ MODKEY,                       XK_s,      spawn,          SHCMD("flameshot gui") }, //Launch FlameShot (ScreenShot tool)
	{ MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("peek") }, //Launch Peek (Video Capture tool)
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("peek") }, //Launch Peek (Video Capture tool)

	//Application Keybindings
	{ MODKEY,                       XK_t,      spawn,          SHCMD("alacritty") }, //Open Terminal
	{ MODKEY|Mod1Mask,              XK_t,      spawn,          SHCMD("st") }, //Open Alternate Terminal
	{ MODKEY,                       XK_w,      spawn,          SHCMD("librewolf") }, //Open Web Browser
	{ MODKEY|Mod1Mask,              XK_w,      spawn,          SHCMD("brave") }, //Open Alternate Web Browser
	{ MODKEY|ControlMask,           XK_w,      spawn,          SHCMD("firefox-esr") }, //Open Secondary Web Browser
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("tor-browser") }, //Open Tor
	{ MODKEY,                       XK_h,      spawn,          SHCMD("alacritty -e htop") }, //Open htop
	{ MODKEY,                       XK_g,      spawn,          SHCMD("steam") }, //Launch Games (Steam)
	{ MODKEY,                       XK_o,      spawn,          SHCMD("obs") }, //Launch OBS
	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("olive") }, //Launch Olive (Video Editor)
	{ MODKEY,                       XK_c,      spawn,          SHCMD("code") }, //Open VS Code
	{ MODKEY|Mod1Mask,              XK_c,      spawn,          SHCMD("alacritty -e bc -l") }, //Open Calculator
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("alacritty -e mc") }, //Open File Manager
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

