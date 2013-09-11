#!/usr/bin/env python
#
# mintest - a minimal C unit testing framework, inspired by minunit
#
# Copyright 2013, Marshall Culpepper
# Licensed under the Apache License, Version 2.0
#
# waf build script for mintest

from waflib.Build import BuildContext

top = '.'
out = 'build'
tests = ('test_asserts', 'test_json', 'test_nl', 'test_printf', 'test_trace')

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

    for test in tests:
        bld.program(target=test,
                    source='tests/%s.c' % test,
                    use=['mintest'])

def test(ctx):
    ctx(rule='../tests/all_tests.py', always=True)

class Test(BuildContext):
    cmd = 'test'
    fun = 'test'
