#ifndef JRTLASER_H
#define JRTLASER_H


class JrtLaser {
  private:
    const int backlightPin = 10;

  public:
    void setup();
  	void loop();
  	void on();
  	void single_shot();
};

#endif