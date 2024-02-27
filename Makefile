# EE569 Homework Assignment #1
# Date: Jan 29, 2023
# Name: Baosheng Chang
# ID: 9660914048
# email: baosheng@usc.edu
#
# Operating Environment: MacOS Monterey, M1 chip

CXX ?= g++

CXXFLAGS += `pkg-config --cflags --libs opencv4`
LDFLAGS += $(shell pkg-config --libs --static opencv4)


%: %.cpp; $(CXX) -std=c++11 $< -o $@ $(CXXFLAGS)
