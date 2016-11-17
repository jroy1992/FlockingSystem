#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <array>
#include <iostream>
#include <string>
#include <random>
#include "Framebuffer.h"
#include "Image.h"
#include "PVector.h"
#include "Flock.h"

int main()
{
    PVector a;
    PVector b(4.0f,5.0f);
    PVector c(7.0f,10.0f);
    a+=b;
    b-=c;
    std::cout<<a<<b;

    std::unique_ptr<frm::Framebuffer> framebuffer( new frm::Framebuffer());
    size_t width=1024;
    size_t height=720;
    framebuffer->init(width, height, NULL);
    Image image(width,height);
    image.setBackground(255,255,255);

    framebuffer->bind();
    framebuffer->poll();

    framebuffer->title("Flock");

    PVector pos(512,360);
    Boid bd(pos);
    Flock f(bd,500);

    while(!framebuffer->shouldClose())
    {
      image.setBackground(255,255,255);
      f.runflock();
      f.draw(image);
      framebuffer->image(image.get(),width,height);
      framebuffer->draw();
      framebuffer->poll();
    }
    return EXIT_SUCCESS;
}
