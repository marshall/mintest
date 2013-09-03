#!/usr/bin/env python
#
# mintest - a minimal C unit testing framework, inspired by minunit
#
# Copyright 2013, Marshall Culpepper
# Licensed under the Apache License, Version 2.0
#
# waf tool for configuring and building mintest

import os

this_dir = os.path.abspath(os.path.dirname(__file__))

def options(opt):
    opt.add_option('--mintest-output', default='human',
                   help='output format [human, json]. default %default')

def configure(cfg):
    out_format = 'MT_OUT_HUMAN'
    if cfg.options.mintest_output.lower() == 'json':
        out_format = 'MT_OUT_JSON'

    cfg.env.append_unique('CFLAGS', ['-DMT_OUT_FORMAT=%s' % out_format])
    cfg.env.append_unique('CXXFLAGS', ['-DMT_OUT_FORMAT=%s' % out_format])
    cfg.env.append_unique('INCLUDES', [os.path.join(this_dir, 'include')])

def build(bld):
    bld.env.MINTEST_SOURCES = bld.root.ant_glob(os.path.join(this_dir[1:], 'src', '**/*.c'))
