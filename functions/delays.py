import time

def delay_ms(val):
    ms = val/1000
    time.sleep(ms)
    return

def delay_us(val):
    us = val/1000000
    time.sleep(us)
    return

def delay_ns(val):
    ns = val/1000000000
    time.sleep(ns)
    return
