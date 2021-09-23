#ifndef POTIMAPPER_H
#define POTIMAPPER_H

class potiMapper {
  public:

    ~potiMapper();
    
    void init(  int in_min, 
                int in_max, 
                float out_min, 
                float out_max, 
                unsigned int in_th,
                float out_offset,
                void (*read_cb)(int *),
                void (*write_cb)(float *, int *),
                bool enableFilter = true
              );

    void setWrite_cb(void (*cb)(float *, int *));
    void setRead_cb(void (*cb)(int *));
    void setInRange(int min, int max);
    void setOutRange(float min, float max);
    void setInThreshold(unsigned int th);
    void setOutOffset(float offset);
    void setFilterAlpha(float alpha); 
    void setFilterEnable(bool enable);
    float getOutVal(void);
    int getInVal(void);
    float getSlope(void);
    int getInThreshold(void);
    float getOutOffset(void);
    float getFilterAlpha(void);
    bool getFilterEnable(void);
    void update(void);
    float maptofloat(int x);

  protected:
    void (*_write_cb)(float *, int *);
    void (*_read_cb)(int *);
    float _val_f = 0.0f;
    int _val_i = 0;
    float _in_min; 
    float _in_max; 
    float _out_min;
    float _out_max;
    int _in_th;
    float _out_offset;
    float _slope;
    bool _enableFilter = false;
    float _alpha = 0.7f;
};

#endif
