//
//  POPTBaseDefine.h
//  poputar
//
//  Created by allen on 15-4-14.
//
//

#ifndef poputar_POPTBaseDefine_h
#define poputar_POPTBaseDefine_h
//开始蓝牙连接次数
#define CONNECT_CONTENT 3

//通知和弦声音是否关闭
#define POPT_CHORD_VOICE "popt_chord_voice"
//主音声音
#define POPT_TOINC_VOICE "popt_toinc_voice"
//通知节拍器是否关闭
#define POPT_METRONOME_VOICE "popt_metronome_voice"
//通知品夹的变换
#define POPT_CAPO_VALUE "popt_capo_value"
//通知试听位置
#define POPT_AUDITION_PAUSE "popt_audition_pause"
#define POPT_AUDITION_RESUME "popt_audition_resume"


#include "POPTStringUtils.h"
#include "POPTHelper.h"
#include "POPTGlobal.h"
#include "POPTVideoPlayer.h"
#include "POPTSlider.h"
#include "BaseLayer.h"
#include "MaskBaseLayer.h"

#include "BLEScene.h"

#include "GameLevelScene.h"
#include "GameLevelMenuItem.h"
#include "GameLevelSingleton.h"

#include "AuditionLayer.h"
#include "GameMenu.h"
#include "MusicMenu.h"
#include "GameConfig.h"
#include "GameRunScene.h"
#include "RunLayer.h"

#include "StartScene.h"
#include "EndLayer.h"
#include "PlayConfig.h"
#include "Section.h"
#include "PlayChord.h"
#include "PlayString.h"

#include "GameLevelInfo.h"
#include "MusicModel.h"

#include <cocos-ext.h>
#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "ui/CocosGUI.h"

#include "PluginHelper.h"

#endif


