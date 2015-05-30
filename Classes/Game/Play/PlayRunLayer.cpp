//
//  FingerRunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "POPTBaseDefine.h"


bool PlayRunLayer::init(const cocos2d::Color4B &color){

    bool result =  initWithColor(color);
    
    //==============设置内容页大小==============
    //画面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //设置大小
    this->setContentSize(Size(visibleSize.width, gameConfig->contentHeight));
    //设置锚点
    this->setAnchorPoint(CCPoint::ZERO);
    float sideHeight = (visibleSize.height-gameConfig->contentHeight)/2;
    //设置位置
    this->setPosition(Point(0,sideHeight));
    
    scheduleUpdate();
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayRunLayer::auditionResume), POPT_AUDITION_RESUME , NULL);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayRunLayer::auditionPause), POPT_AUDITION_PAUSE , NULL);
    
    //初始化伴奏信息
    accPlaying = false;
    
    accFileName= "music/stage/"+POPTStringUtils::intToString(poptGlobal->gni->getGameLevelInfo()->getLevel())+"/"+poptGlobal->gni->getMusic()+".mp3";
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(accFileName.c_str());
    
    currentSection=-1;
    blueToothSection = -1;
    
    return result;
}

PlayRunLayer::~PlayRunLayer(){
    __NotificationCenter::getInstance()->removeObserver(this, POPT_AUDITION_RESUME);
    __NotificationCenter::getInstance()->removeObserver(this, POPT_AUDITION_PAUSE);
    
    delete gameConfig;
}


PlayRunLayer* PlayRunLayer::createPlayRunLayer(MusicModel *musicModel,float height){
    PlayRunLayer *layer = new PlayRunLayer();
    if(layer && layer->init4Finger(Color4B(0,0,0,0),musicModel,height))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PlayRunLayer::init4Finger(const cocos2d::Color4B &&color, MusicModel *musicModel,float height){
    //画面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    gameConfig = new PlayConfig(visibleSize.width, height, musicModel);
    poptGlobal->gni->setConfig(gameConfig);
    bool result =  init(color);
    //组装界面
    this->loadFrame();
    //正式层
    sectionLayer = loadSectionLayer(true);
    this->addChild(sectionLayer,2);
    //试听层
    testSectionLayer = loadSectionLayer(false);
    this->addChild(testSectionLayer);
    
    //加载音乐
    map<int,SectionInfo*> sections = gameConfig->musicModel->getSections();
    int size =  (int)sections.size();
    for (int i=1; i<size+1; i++) {
        SectionInfo* sectionInfo = sections[i];
        map<int,BeatInfo*> beats = sectionInfo->beats;
        for (int b=0; b<beats.size(); b++) {
            BeatInfo* beatInfo =  beats.at(b+1);
            string type = beatInfo->chordType;
            string chordFileName = "audio/chord/"+type+"_clean.caf";
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(chordFileName.c_str());
        }
        map<int,TonicInfo*> tonics = sectionInfo->tonics;
        for (int t=1; t<tonics.size()+1; t++) {
            TonicInfo* toincInfo = tonics[t];
            string note4Str = toincInfo->note;
            if(!note4Str.empty() && note4Str !="0" ){
                string scaleFileName ="audio/scale/"+note4Str+".mp3";
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(scaleFileName.c_str());
            }
        }
    }
    //开始移动正式音符界面
    auto beginMove = getMoveActionIterval();
    sectionLayer->runAction(beginMove);
    
    return result;
}

Layer* PlayRunLayer::loadSectionLayer(bool isFormal){
    
    tonic2StrSingleton->loadCurrentTonic(poptGlobal->gni->getMusicModel()->getKey());

    int sectionIndex = 1;
    auto sectionLayer = Layer::create();
    sectionLayer->setAnchorPoint(Vec2::ZERO);
    sectionLayer->setPosition(Vec2(-gameConfig->startX,0));
    //增加前置小节
    int beforeType;
    if(isFormal){
        beforeType = SECTION_SHOW;
    }else{
        beforeType = SECTION_NONE;
    }
    for (int i=0; i<gameConfig->beforSectionSize; i++) {
        Section* section = Section::createSection(nullptr,sectionIndex,beforeType,0,0);
        section->setDelegate(this);
        sectionLayer->addChild(section);
        if(isFormal){
            sectionSprite.insert(sectionIndex, section);
        }
        sectionIndex++;
    }
    
    //增加正式小节
    int type;
    if(isFormal){
        if(gameConfig->musicModel->getType()==MUSICMODEL_TYPE_CHORD){
            type = SECTION_FORMAL_CHORD;
        }else if(gameConfig->musicModel->getType()==MUSICMODEL_TYPE_TONIC){
            type = SECTION_FORMAL_TONIC;
        }
    }else{
        type = SECTION_AUDITION;
    }
    map<int,SectionInfo*> sections = gameConfig->musicModel->getSections();
    map<int,MusicPlayInfo*> plays = gameConfig->musicModel->getPlayInfo();
    //循环播放模式
    for (int p = 1; p<plays.size()+1; p++) {
        MusicPlayInfo* playInfo =  plays[p];
        int startSectionIndex = playInfo->startSection;
        int endSectionIndex = playInfo->endSection;
        
        for (int s = startSectionIndex; s<=endSectionIndex; s++) {
            SectionInfo* sectionInfo = sections[s];
            Section* section = Section::createSection(sectionInfo,sectionIndex,type,playInfo->p_index,s);
            section->setDelegate(this);
            sectionLayer->addChild(section);
            if(isFormal){
                sectionSprite.insert(sectionIndex, section);
            }
            sectionIndex++;
        }
    }
    
    //增加后置小节
    int afterType;
    if(isFormal){
        afterType = SECTION_SHOW;
    }else{
        afterType = SECTION_NONE;
    }
    for (int i=0; i<gameConfig->afterSectionSize; i++) {
        Section* section = Section::createSection(nullptr,sectionIndex,beforeType,0,0);
        section->setDelegate(this);
        sectionLayer->addChild(section);
        if(isFormal){
            sectionSprite.insert(sectionIndex, section);
        }
        sectionIndex++;
    }
    
    tonic2StrSingleton->unLoadTonic();
    return sectionLayer;
}

void PlayRunLayer::loadFrame(){
    //节奏线碰撞时的动画效果
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("game/play/hitline_blink.png");
    animation->setDelayPerUnit(0.3f);
    animation->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animation, "hitline_blink");
    
    //增加撞线
    auto mRhythm = ui::Scale9Sprite::create("game/play/hitline.png");
    mRhythm->setAnchorPoint(Vec2(0.5,0));
    mRhythm->setPosition(Vec2(gameConfig->impactLine, 0));
    mRhythm->setPreferredSize(Size(mRhythm->getContentSize().width,gameConfig->contentHeight-gameConfig->chordHeight));
    mRhythm->setTag(8001);
    this->addChild(mRhythm,3);

    //和弦区域的底图
    if(gameConfig->musicModel->getType()==MUSICMODEL_TYPE_CHORD){
        auto chordBanner = Sprite::create("game/play/chordbanner.png");
        chordBanner->setPosition(Vec2(0,gameConfig->contentWidth-gameConfig->chordHeight));
        this->addChild(chordBanner);
    }

    //弦间的高度
    int stringCount = 5;
    for (int i=0; i<6; i++) {
        float stringHeight = gameConfig->stringUnitHeight*stringCount;
        stringMap[i+1]=Value(stringHeight);
        
        ui::Scale9Sprite *mString = ui::Scale9Sprite::create("game/play/string.png");
        mString->setPreferredSize(Size(Vec2(gameConfig->contentWidth, mString->getContentSize().height)));
        //设置弦的位置 Y轴：距离下边界的位置+弦的位置
        mString->setPosition(Vec2(gameConfig->contentWidth/2,gameConfig->stringSideHeight+stringHeight));
        this->addChild(mString,1);
        
        stringCount-=1;
    }
}

void PlayRunLayer::update(float at){
    
    //当前音乐层距离撞线的位置
    int playType;
    if(gameConfig->musicModel->getType()==MUSICMODEL_TYPE_CHORD){
        playType = UPDATE_TYPE_CHORD;
    }else if(gameConfig->musicModel->getType()==MUSICMODEL_TYPE_TONIC){
        playType = UPDATE_TYPE_TONIC;
    }
    sectionNotice(playType);
    sectionNotice(UPDATE_TYPE_BLUETOOTH);
}



void PlayRunLayer::sectionNotice(int type){
    float distance=0;
    if(isAudition){
        distance = testSectionLayer->getPositionX()-gameConfig->impactLine;
    }else{
        distance = sectionLayer->getPositionX()-gameConfig->impactLine;
    }
    
    if(type==UPDATE_TYPE_BLUETOOTH){ //蓝牙发送提前一个音符的位置
        distance-=gameConfig->unitWidth;
    }
    int currFlag=-1;
    float currFlagTemp = (distance*-1)/gameConfig->sectionWidth;
    
    float relativePosX ;
    if(currFlagTemp>=0){
        currFlag = (int)currFlagTemp;
        
        relativePosX = distance*-1 - gameConfig->sectionWidth*(float)(currFlag);
        
        if (type==UPDATE_TYPE_CHORD||type==UPDATE_TYPE_TONIC) {
            if(currFlag>=0 && currFlag !=currentSection){
                currentSection = currFlag;
            }
            Section* section =  sectionSprite.at(currentSection+1);
            if(section!=NULL){
                bool result = section->updateState(relativePosX,type);
                if(result){
                    //是否相撞
                    //auto loading = AnimationCache::getInstance()->getAnimation("hitline_blink");
                    //auto animate = Animate::create(loading);
                    //auto rhythm = this->getChildByTag(8001);
                    //rhythm->runAction(animate); //九宫格不能自动执行动画
                }
                
                if(result && !accPlaying){
                    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(accFileName.c_str(),false);
                    accPlaying = true;

                }
            }
        }else if(type==UPDATE_TYPE_BLUETOOTH){
            if(currFlag>=0 && currFlag !=blueToothSection){
                blueToothSection = currFlag;
            }
            
            Section* section =  sectionSprite.at(blueToothSection+1);
            if(section!=NULL){
                section->updateState(relativePosX,type);
            }
        }
    }
}


void PlayRunLayer::endAnimationSetting(){
    //通知和弦发声
    __Bool* chordVoice = __Bool::create(false);
    __NotificationCenter::getInstance()->postNotification(POPT_CHORD_VOICE,chordVoice);
    //通知主音发声
    __Bool* toincVoice = __Bool::create(false);
    __NotificationCenter::getInstance()->postNotification(POPT_TOINC_VOICE,toincVoice);
    //通知节拍器发声
    __Bool* metronomeVoice = __Bool::create(true);
    __NotificationCenter::getInstance()->postNotification(POPT_METRONOME_VOICE,metronomeVoice);
}


//试听功能
void PlayRunLayer::audition(bool isAudition){
    MusicModel* musicModel =  poptGlobal->gni->getMusicModel();

    this->isAudition = isAudition;
    //试听
    if(isAudition){
        if(accPlaying){
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        
        if(musicModel->getType() == MUSICMODEL_TYPE_CHORD){
            //通知和弦发声
            __Bool* chordVoice = __Bool::create(true);
            __NotificationCenter::getInstance()->postNotification(POPT_CHORD_VOICE,chordVoice);
        }else if(musicModel->getType() == MUSICMODEL_TYPE_TONIC){
            //通知主音发声
            __Bool* toincVoice = __Bool::create(true);
            __NotificationCenter::getInstance()->postNotification(POPT_TOINC_VOICE,toincVoice);
        }
        testSectionLayer->setPositionX(sectionLayer->getPositionX());
        sectionLayer->pause(); //暂停正式音符界面
    }else{
        if(accPlaying){
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
        
        if(musicModel->getType() == MUSICMODEL_TYPE_CHORD){
            //通知和弦发声
            __Bool* chordVoice = __Bool::create(false);
            __NotificationCenter::getInstance()->postNotification(POPT_CHORD_VOICE,chordVoice);
        }else if(musicModel->getType() == MUSICMODEL_TYPE_TONIC){
            //通知主音发声
            __Bool* toincVoice = __Bool::create(false);
            __NotificationCenter::getInstance()->postNotification(POPT_TOINC_VOICE,toincVoice);
        }
        
        auditionControll(AUDITION_PAUSE);
        sectionLayer->resume();  //恢复正式音符界面移动
    }
}

//移动动作
ActionInterval* PlayRunLayer::getMoveActionIterval(){
    MusicModel* musicModel =  poptGlobal->gni->getMusicModel();
    map<int,SectionInfo*> sections = musicModel->getSections();
    
    //小节总宽度
    float sectionWidth = gameConfig->sectionWidth;
    //计算小节个数
    map<int,MusicPlayInfo*> plays =  musicModel->getPlayInfo();
    int sectionSize=0;
    for (int p=1; p<plays.size()+1; p++) {
        MusicPlayInfo* playInfo = plays[p];
        int startIndex = playInfo->startSection;
        int endIndex = playInfo->endSection;
        sectionSize+=(endIndex-startIndex)+1;
    }
    
    //加上前置小节
    sectionSize+= gameConfig->beforSectionSize;
    
    int moveCount = (int)gameConfig->contentWidth/(int)sectionWidth;
    if((int)gameConfig->contentWidth%(int)sectionWidth >0){
        moveCount+=1;
    }
    moveCount+=sectionSize;
    
    //从开始到撞击线的距离
    float distance = gameConfig->rhythmWidth;
    //因第一个和弦到撞击需要走一个距离所以初始化为1
    int count = 1;
    //计算和弦总宽度到据撞击线位置的距离
    count += (int)(sectionSize*sectionWidth)/(int)distance;
    //如果有超出则会+1
    if((int)(moveCount*sectionWidth)%(int)distance>0){
        count+=1;
    }
    //移动时间
    float time = gameConfig->allTime*count;
    MoveBy *beginMove = MoveBy::create(time, Vec2(-distance*count,0));
    return beginMove;
}

//试听控制
void PlayRunLayer::auditionControll(int type){
    switch (type) {
        case AUDITION_PAUSE:
            testSectionLayer->pause();
            testSectionLayer->stopAllActions();
            break;
        case AUDITION_RESUME:
            testSectionLayer->resume();
            testSectionLayer->runAction(getMoveActionIterval()); //移动试听音符界面
            break;
        default:
            break;
    }
}

void PlayRunLayer::sectionPause(){
    if(accPlaying){
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    sectionLayer->pause();
};

void PlayRunLayer::sectionResume(){
    if(accPlaying){
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
    sectionLayer->resume();
};


void PlayRunLayer::auditionResume(Ref* ref){
    testSectionLayer->stopAllActions();
    //1.获得试听时间轴拖动的位置
    auto value = (__Float*)ref;
    //时间轴当前位置应该移动的距离
    float currentX = value->getValue() * gameConfig->move4sec;
    
    //前置小节的宽度
    float beforSectionWidth = gameConfig->beforSectionSize*gameConfig->sectionWidth;
    //开始小节的宽度-画面宽度为第0秒和弦层的位置
    //第0秒和弦层位置 - 当前应该移动的位置  = 当前和弦层的位置
    float auditionX = -(beforSectionWidth-gameConfig->contentWidth)-currentX;
    testSectionLayer->setPositionX(auditionX);
    auditionControll(AUDITION_RESUME);
    log("test X:%f",auditionX);
}


void PlayRunLayer::auditionPause(cocos2d::Ref *ref){
    auditionControll(AUDITION_PAUSE);
}

void PlayRunLayer::lyricCallbak(int p, int s, int t){
    //根据当前的播放顺序，小节数和主音获得歌词的内容
     //log("p:%i   s:%i   t:%i",p,s,t);
    _delegate->lyricCallback(p,s,t);
}


void PlayRunLayer::setDelegate(PlayRunLayerDelegate *delegate){
    _delegate = delegate;
}

void PlayRunLayer::onExit(){
    
    if(accPlaying){
        CocosDenshion::SimpleAudioEngine::getInstance()->end();
//        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        accPlaying = false;
    }
    
    //卸载音乐
    map<int,SectionInfo*> sections = gameConfig->musicModel->getSections();
    int size =  (int)sections.size();
    for (int i=1; i<size+1; i++) {
        SectionInfo* sectionInfo = sections[i];
        map<int,BeatInfo*> beats = sectionInfo->beats;
        for (int b=0; b<beats.size(); b++) {
            BeatInfo* beatInfo =  beats.at(b+1);
            string type = beatInfo->chordType;
            string chordFileName = "audio/chord/"+type+"_clean.caf";
            CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(chordFileName.c_str());
        }
        map<int,TonicInfo*> tonics = sectionInfo->tonics;
        for (int t=1; t<tonics.size()+1; t++) {
            TonicInfo* toincInfo = tonics[t];
            string note4Str = toincInfo->note;
            if(!note4Str.empty() && note4Str !="0" ){
                string scaleFileName ="audio/scale/"+note4Str+".mp3";
                CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(scaleFileName.c_str());
            }
        }
    }
    
    Layer::onExit();
}