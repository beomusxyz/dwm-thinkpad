/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx	= 1;        /* border pixel of windows */
static const unsigned int gappx		= 10;        /* gaps between windows */
static const unsigned int snap		= 32;       /* snap pixel */
static const int swallowfloating	= 0;        /* 1 means swallow floating windows by default */
static const int showbar		= 1;        /* 0 means no bar */
static const int topbar			= 1;        /* 0 means bottom bar */
static const char *fonts[]		= { "Terminus:size=9", "fontawesome:size=9" };
static const char dmenufont[]		= "Terminus:size=9";
static const char col_gray1[]		= "#222222";
static const char col_gray2[]		= "#444444";
static const char col_gray3[]		= "#bbbbbb";
static const char col_gray4[]		= "#eeeeee";
static const char col_cyan[]		= "#005577";
static const char col_Yale[]		= "#004385";
static const char col_SlateRed[]	= "#D1615D";
static const char col_LightningII[]	= "#3B6185";
static const char col_SkyBlue[]		= "#628bc3";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_SkyBlue,  col_SkyBlue },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
//	{ "Gimp",      NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "Firefox",   NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",     NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,        NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "20", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *xlock[]    = { "xsecurelock", NULL};
static const char *brightnessup[] = {"light", "-A", "5", NULL};
static const char *brightnessdown[] = {"light", "-U", "5", NULL};
static const char *timetable[] = {"feh", "/home/beomus/Pictures/timetable.png", NULL};
static const char *screenshot[] = {"scrot", "/home/beomus/Pictures/Screenshots/%Y-%m-%d-%T-screenshot.jpg", NULL};
static const char *browser[] = {"librewolf", NULL};
static const char *mail[] = {"thunderbird", NULL};
static const char *mixer[] = {"st", "pulsemixer", NULL};
static const char *ncmpcpp[] = {"st", "ncmpcpp", NULL};
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */


	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,			XK_l,      spawn,          {.v = xlock } },
	{ MODKEY|ShiftMask,		XK_t,	   spawn,	   {.v = timetable} },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   {.v = screenshot} },
	{ MODKEY,			XK_b,	   spawn,	   {.v = browser} },
	{ MODKEY,			XK_p,	   spawn,	   {.v = mixer} },
	{ MODKEY,			XK_m,	   spawn,	   {.v = mail} },
	{ MODKEY,			XK_n,	   spawn,	   {.v = ncmpcpp} },
	
//long ass entries start
	{ 0,			XF86XK_MonBrightnessUp,		spawn,	   {.v = brightnessup} },
	{ 0,			XF86XK_MonBrightnessDown,	spawn, 	   {.v = brightnessdown} },
	{ 0,			XF86XK_AudioPlay,		spawn,	   SHCMD("mpc toggle") },
	{ 0,			XF86XK_AudioNext,		spawn,	   SHCMD("mpc next") },
	{ 0,			XF86XK_AudioPrev,		spawn,	   SHCMD("mpc prev") },
	{ 0,			XK_Insert, spawn,	   	SHCMD("xdotool type $(grep -v '^#' ~/.local/share/bookmarks/bookmarks.txt | dmenu -i -l 50 | cut -d' ' -f1)") },
//long ass entries end

	{ MODKEY|ShiftMask,		XK_a,	   spawn,	   {.v = (const char*[]){"bookmarkthis", "NULL"} } },
	{ MODKEY,                       XK_t,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY,			XK_Right,  shiftview,	   {.i = +1 },},
	{ MODKEY,			XK_Left,   shiftview,      {.i = -1 },},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

