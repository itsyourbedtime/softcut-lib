//
// Created by emb on 11/10/18.
//

#ifndef Softcut_Softcut_H
#define Softcut_Softcut_H

#include <memory>
#include <thread>
#include "Types.h"
#include "Voice.h"

namespace softcut {
    template<int numVoices>
    class Softcut {
    protected:
        friend class TestBuffers;

    public:

//        Softcut(sample_t **buffers, size_t numBuffers, size_t numFrames) {
//
//            for (int v = 0; v < numVoices; ++v) {
//                scv[v].setBuffer(buffers[v % numBuffers], numFrames);
//            };
//            this->reset();
//        }

        Softcut() {
            this->reset();
        }

        void reset() {
            for (int v = 0; v < numVoices; ++v) {
                scv[v].reset();
            };
        }

        // assumption: v is in range
        void processBlock(int v, float *in, float *out, int numFrames) {
            scv[v].processBlockMono(in, out, numFrames);
        }

        void setSampleRate(unsigned int hz) {
            for (auto &v : scv) {
                v.setSampleRate(hz);
            }
        }

        void setRate(int voice, float rate) {
            scv[voice].setRate(rate);
        }

        void setLoopStart(int voice, float sec) {
            scv[voice].setLoopStart(sec);
        }

        void setLoopEnd(int voice, float sec) {
            scv[voice].setLoopEnd(sec);
        }

        void setLoopFlag(int voice, bool val) {
            scv[voice].setLoopFlag(val);
        }

        void setFadeTime(int voice, float sec) {
            scv[voice].setFadeTime(sec);
        }

        void setRecLevel(int voice, float amp) {
            scv[voice].setRecLevel(amp);
        }

        void setPreLevel(int voice, float amp) {
            scv[voice].setPreLevel(amp);
        }

        void setRecFlag(int voice, bool val) {
            scv[voice].setRecFlag(val);
        }

        void setPlayFlag(int voice, bool val) {
            scv[voice].setPlayFlag(val);
        }

        void setPosition(int voice, float sec) {
            scv[voice].setPosition(sec);
        }

        void setPreFilterFc(int voice, float x) {
            (void) voice;
            (void) x;
            scv[voice].setPreFilterFc(x);
        }

        void setPreFilterRq(int voice, float x) {
            (void) voice;
            (void) x;
            // FIXME: disabled for now
            // scv[voice].setPreFilterRq(x);
        }

        void setPreFilterLp(int voice, float x) {
            (void) voice;
            (void) x;
            // FIXME: disabled for now
            // scv[voice].setPreFilterLp(x);
        }

        void setPreFilterHp(int voice, float x) {
            (void) voice;
            (void) x;
            // FIXME: disabled for now
            // scv[voice].setPreFilterHp(x);
        }

        void setPreFilterBp(int voice, float x) {
            (void) voice;
            (void) x;
            // FIXME: disabled for now
            // scv[voice].setPreFilterBp(x);
        }

        void setPreFilterBr(int voice, float x) {
            (void) voice;
            (void) x;
            // FIXME: disabled for now
            // scv[voice].setPreFilterBr(x);
        }

        void setPreFilterDry(int voice, float x) {
            (void) voice;
            (void) x;
            // FIXME: disabled for now
            // scv[voice].setPreFilterDry(x);
        }

        void setPreFilterFcMod(int voice, float x) {
            scv[voice].setPreFilterFcMod(x);
        }

        void setPostFilterFc(int voice, float x) {
            scv[voice].setPostFilterFc(x);
        }

        void setPostFilterRq(int voice, float x) {
            scv[voice].setPostFilterRq(x);
        }

        void setPostFilterLp(int voice, float x) {
            scv[voice].setPostFilterLp(x);
        }

        void setPostFilterHp(int voice, float x) {
            scv[voice].setPostFilterHp(x);
        }

        void setPostFilterBp(int voice, float x) {
            scv[voice].setPostFilterBp(x);
        }

        void setPostFilterBr(int voice, float x) {
            scv[voice].setPostFilterBr(x);
        }

        void setPostFilterDry(int voice, float x) {
            scv[voice].setPostFilterDry(x);
        }

#if 0 // not allowing realtime manipulation of fade logic params
        void setPreFadeWindow(float x) {
    auto t = std::thread([x] {
        FadeCurves::setPreWindowRatio(x);
    });
    t.detach();
}

void setRecFadeDelay(float x) {
    auto t = std::thread([x] {
        FadeCurves::setRecDelayRatio(x);
    });
    t.detach();
}

void setPreFadeShape(float x) {
    auto t = std::thread([x] {
        FadeCurves::setPreShape(static_cast<FadeCurves::Shape>(x));
    });
    t.detach();
}

void setRecFadeShape(float x) {
    auto t = std::thread([x] {
        FadeCurves::setRecShape(static_cast<FadeCurves::Shape>(x));
    });
    t.detach();
}
#endif

        void setRecOffset(int i, float d) {
            scv[i].setRecOffset(d);
        }

        void setLevelSlewTime(int i, float d) {
            scv[i].setLevelSlewTime(d);
        }

        void setRecPreSlewTime(int i, float d) {
            scv[i].setRecPreSlewTime(d);
        }

        void setRateSlewTime(int i, float d) {
            scv[i].setRateSlewTime(d);
        }

        phase_t getQuantPhase(int i) {
            return scv[i].getQuantPhase();
        }

        void setPhaseQuant(int i, phase_t q) {
            scv[i].setPhaseQuant(q);
        }

        void setPhaseOffset(int i, float sec) {
            scv[i].setPhaseOffset(sec);
        }

        bool getRecFlag(int i) {
            return scv[i].getRecFlag();
        }

        bool getPlayFlag(int i) {
            return scv[i].getPlayFlag();
        }

        void syncVoice(int follow, int lead, float offset) {
            scv[follow].setPosition(scv[lead].getPos() + offset);
        }

        void setVoiceBuffer(int i, float *buf, size_t bufFrames) {
            scv[i].setBuffer(buf, bufFrames);
        }

        void setPreFilterQ(int i, float x) {
            scv[i].setPreFilterQ(x);
        }
        void setPreFilterEnabled(int i, bool x) {
            scv[i].setPreFilterEnabled(x);
        }

    private:
        Voice scv[numVoices];
    };
}


#endif //Softcut_Softcut_H2