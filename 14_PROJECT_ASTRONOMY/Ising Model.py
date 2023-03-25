# Imports
import numpy as np
from numpy import random as rnd
from matplotlib import pyplot as plt
import os,sys,warnings,datetime,time,itertools,math
from pynput import keyboard

# Global parameters
running = True

# Callback function upon ESC press
def on_press(key):
    global running
    if key==keyboard.Key.esc:
        running = False
# Update rules for the screen, iterates the neighborhood of all particles and computes next spin
def update_screen(screen,H=0,beta=1):
    for m in range(screen.shape[0]):
        for n in range(screen.shape[1]):
            neighborhood_spin = 0
            for ij in itertools.product([-1,0,1],repeat=2):
                if ij==(0,0): continue
                targetM = m + ij[0]
                targetN = n + ij[1]
                if targetM<0 or targetM>screen.shape[0]-1: continue 
                if targetN<0 or targetN>screen.shape[1]-1: continue 
                neighborhood_spin += screen[targetM,targetN]
            b = neighborhood_spin + H
            ppos = 1/(1 + np.exp(-2*beta*b))
            pneg = 1 - ppos
            ccolor = rnd.choice(a=[-1,1],p=[pneg,ppos])
            screen[m,n] = ccolor
    return screen
# Main function
def main():
    global running
    # Create initial screen
    screen = rnd.choice(
        a=[-1,1],
        p=[0.5,0.5],
        size=[128,128]
    )
    # Listen for ESC keypress
    listener = keyboard.Listener(on_press=on_press)
    listener.start()
    # Call main loop
    while running:
        screen = update_screen(
            screen,
            H=0.0
        )
        # Plot screen
        plt.imshow(screen)
        plt.pause(0.1)
    return

# Main function call
if __name__=='__main__': main()