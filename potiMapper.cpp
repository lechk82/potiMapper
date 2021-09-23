#include "potiMapper.h"
#include "Arduino.h"

potiMapper::~potiMapper(){return;};

void potiMapper::init(int in_min, 
                int in_max, 
                float out_min, 
                float out_max, 
                unsigned int in_th,
                float out_offset,
                void (*read_cb)(int *),
                void (*write_cb)(float *, int *),
                bool enableFilter = true
              ){
    _in_min = in_min;
    _in_max = in_max;
    _out_min = out_min;
    _out_max = out_max;
    _in_th = in_th;
    _out_offset = out_offset;
    _slope = (_out_max-_out_min)/((float)_in_max-(float)_in_min);
    _enableFilter = enableFilter;
    setRead_cb(read_cb);
    setWrite_cb(write_cb);
}

void potiMapper::setWrite_cb(void (*cb)(float *, int *)){  _write_cb = cb; }
void potiMapper::setRead_cb(void (*cb)(int *)){ _read_cb = cb; }
void potiMapper::setInRange(int min, int max){
    _in_min = min;
    _in_max = max;
    _slope = (_out_max-_out_min)/((float)_in_max-(float)_in_min);
}
void potiMapper::setOutRange(float min, float max){
    _out_min = min;
    _out_max = max;
    _slope = (_out_max-_out_min)/((float)_in_max-(float)_in_min);
}
void potiMapper::setInThreshold(unsigned int th){ _in_th = th; }
void potiMapper::setOutOffset(float offset){ _out_offset = offset; }
void potiMapper::setFilterAlpha(float alpha){ _alpha = alpha; }
void potiMapper::setFilterEnable(bool enable){ _enableFilter = enable; }
float potiMapper::maptofloat(int x){ 
    return _out_min + ((float)x-(float)_in_min)*_slope;
}
float potiMapper::getOutVal(void){ return _val_f; }
int potiMapper::getInVal(void){ return _val_i; }
float potiMapper::getSlope(void){ return _slope; }
int potiMapper::getInThreshold(void){ return _in_th; }
float potiMapper::getOutOffset(void){ return _out_offset; }
float potiMapper::getFilterAlpha(void){ return _alpha; }
bool potiMapper::getFilterEnable(void){ return _enableFilter; }

void potiMapper::update(){
int read;
    _read_cb(&read);
    if(_enableFilter){
        // Exp Moving Avarage (EMA) Filter y(n) = (1 - alpha) * y(n-1) + alpha * x(n)
        // 3db cutoff frequency: f = Fs/(2*pi) * acos(1 - alpha^2 / (2*(1-alpha)))
        read = (int)round(_alpha * (float)read) + ((1.0f-_alpha)*(float)_val_i);
    }
    if((read > _val_i+_in_th) || (read < _val_i-_in_th)){
        _val_i = read;
        _val_f  = maptofloat(read) + _out_offset;
        _write_cb(&_val_f, &_val_i);
    }
}
