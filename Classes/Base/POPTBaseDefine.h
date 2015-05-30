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
//通知试听暂定
#define POPT_AUDITION_PAUSE "popt_audition_pause"
//通知试听继续
#define POPT_AUDITION_RESUME "popt_audition_resume"


//=======================模型=========================
//游戏关卡模型
#include "GameLevelInfo.h"
//游戏音乐模型
#include "MusicModel.h"
//歌词模型
#include "LyricModel.h"


//=======================基础信息=========================
//string帮助类
#include "POPTStringUtils.h"
//帮助类
#include "POPTHelper.h"
//全区属性  --单例
#include "POPTGlobal.h"
//ios蓝牙帮助类
#include "PluginHelper.h"
//重新的播放器
#include "POPTVideoPlayer.h"
//重写的时间轴
#include "POPTSlider.h"
//遮罩层的父类
#include "MaskBaseLayer.h"

#include "POPTTonic2StrSingleton.h"



//=======================场景=========================
//蓝牙连接场景
#include "BLEScene.h"
//音乐信息转换为十六进制蓝牙信息
#include "MusicAnalysis.h"


//关卡场景
#include "GameLevelScene.h"
#include "GameLevelMenuItem.h"
#include "GameLevelSingleton.h"
#include "GameLevelCardReader.h"
#include "GameLevelCardHandler.h"



#include "AuditionLayer.h"
#include "GameRunScene.h"
#include "PlayRunLayer.h"
#include "StartScene.h"
#include "EndLayer.h"
#include "PlayConfig.h"
#include "Section.h"
#include "PlayChord.h"
#include "PlayString.h"
#include "Lyric.h"
#include "PassSence.h"



#include <cocos-ext.h>
#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UIVideoPlayer.h"
//声音引擎
#include "SimpleAudioEngine.h"

#endif


