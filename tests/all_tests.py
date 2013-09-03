#!/usr/bin/env python
'''
mintest - a minimal C unit testing framework, inspired by minunit

Copyright 2013, Marshall Culpepper
Licensed under the Apache License, Version 2.0

python based unit test driver for mintest self-tests
'''
import json
import os
import unittest
import subprocess

this_dir = os.path.abspath(os.path.dirname(__file__))
build_dir = os.path.join(os.path.dirname(this_dir), 'build')

class OutputTest(unittest.TestCase):
    binary = None

    def setUp(self):
        self.proc = subprocess.Popen([self.binary], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        self.rc = self.proc.wait()
        self.out = self.proc.stdout.read()

class TestAsserts(OutputTest):
    binary = os.path.join(build_dir, 'test_asserts')

    def runTest(self):
        self.assertEqual(self.rc, 0)

class TestJson(OutputTest):
    binary = os.path.join(build_dir, 'test_json')

    def runTest(self):
        self.assertEqual(self.rc, 3)
        try:
            data = json.loads(self.out)
        except Exception, e:
            self.fail(str(e))

        self.assertEqual(data['passed'], 2)
        self.assertEqual(data['failed'], 3)
        self.assertEqual(data['total'], 5)

        failures = data['failures']
        self.assertEqual(len(failures), 3)
        self.assertEqual(failures[0]['test'], 'assert_msg_fail')
        self.assertEqual(failures[1]['test'], 'assert_fail')
        self.assertEqual(failures[2]['test'], 'failed')

class TestNL(OutputTest):
    binary = os.path.join(build_dir, 'test_nl')

    def runTest(self):
        self.assertEqual(self.rc, 1)
        self.assertTrue('[END]\r\n' in self.out)

class TestPrintf(OutputTest):
    binary = os.path.join(build_dir, 'test_printf')

    def runTest(self):
        self.assertEqual(self.rc, 1)
        lines = self.out.splitlines()
        for line in lines:
            self.assertTrue(line.startswith('[CUSTOM]'))

if __name__ == '__main__':
    unittest.main()
