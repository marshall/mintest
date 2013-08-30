#!/usr/bin/env python
# waf build script for mintest

from waflib.Build import BuildContext

top = '.'
out = 'build'

def options(opt):
    opt.load('mintest', tooldir='.')

def configure(cfg):
    cfg.load('mintest', tooldir='.')
    cfg.load('gcc')

def build(bld):
    bld.load('mintest', tooldir='.')

    bld.stlib(target='mintest',
              name='mintest',
              source=bld.env.MINTEST_SOURCES)

    bld.program(target='all_tests',
                source=bld.path.ant_glob('tests/**/*.c'),
                use=['mintest'])

def test(ctx):
    ctx(rule='./all_tests', always=True)

class Test(BuildContext):
    cmd = 'test'
    fun = 'test'
