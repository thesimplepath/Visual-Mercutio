#!/bin/sh
scp src/.libs/libeasysoap.so.0 \
	tests/.libs/interopserver \
	tests/.libs/interopclient \
	validator/.libs/validator \
	simpleserver/.libs/simpleserver \
	dcrowley@easysoap.sourceforge.net:/home/groups/e/ea/easysoap/bin/
