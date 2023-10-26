#include "Invader.h"


void Invader::loadSounds(){
        std::vector<std::string> sound_files={
        "ALARMA.WAV"
        ,"BOMBOUT.WAV"
        ,"BOSSEX.WAV"
        ,"C_OK.WAV"
        ,"C_OPTION.WAV"
        ,"EXPLOS1.WAV"
        ,"FEBLE.WAV"
        ,"LAMEVAEX.WAV"
        ,"MECANIC.WAV"
        ,"NAUMARE0.WAV"
        ,"SHOT0.WAV"
        ,"SHOT1.WAV"
        ,"SHOT2.WAV"
        ,"TRO.WAV"
        ,"TURBO.WAV"
        ,"ATTENTIO.WAV"
        ,"BOMBERUP.WAV"
        ,"HUMET.WAV"
        ,"POWERUP.WAV"
        ,"ROBOT.WAV"

    };

    for(auto sound_file:sound_files){
        Sound::newSound(sound_file,"../../../assets/sounds/"+sound_file);
    }
}