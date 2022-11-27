EXTENSION       = url
MODULE_big		= url
DATA            = url--1.0.sql url.control

LDFLAGS         = -lrt

HEADERS			= urlType.h

OBJS			= url.o urlType.o

PG_CONFIG       ?= pg_config
PGXS            = $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)