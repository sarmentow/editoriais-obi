#!/usr/bin/env python3
import click
import time
import os
from subprocess import call


basename = os.path.basename
splitext = os.path.splitext 
@click.command()
@click.argument('script', type=click.Path(exists=True))
@click.argument('folder', type=click.Path(exists=True))
@click.option('--lang', default="cpp") 
@click.option('--debug', default=True)
def corretor(script, folder, lang, debug):
    for root, dirs, files in os.walk(folder):
        if root != folder:
            solutions = [f for f in files if '.sol' in f]
            inputs = [f for f in files if '.in' in f]
            inputs.sort(key=lambda name: int(splitext(basename(name))[0]))
            solutions.sort(key=lambda name: int(splitext(basename(name))[0]))
            processes = []
            for inp, sol in zip(inputs, solutions):
                inp = os.path.join(root, inp)
                sol = os.path.join(root, sol)
                if lang == "python":
                    call(f'cat {inp} | python {script} | diff {sol} -', shell=True)
                elif lang == "cpp":
                    if debug:
                        print(inp)
                      #  print("Output:")
                      #  call(f'cat {inp} | {script}', shell=True)
                      #  print("Answer:")
                      #  call(f'cat {sol}', shell=True)
                    call(f'cat {inp} | {script} | diff {sol} -', shell=True)
                    if debug:
                        print()
                        time.sleep(.1)
                
                
if __name__ == "__main__":
    corretor()

        
        
