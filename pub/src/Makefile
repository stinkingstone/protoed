TARGET_LIB := liblhs_pub.a
PUBDIR=..

SRCS := cfg_parse.cpp \
	format.cpp \
	para_parse.cpp \
	lhs_log.cpp

cppfiles=$(notdir $(SRCS))
OBJPATH = $(PUBDIR)/obj
BINPATH = $(PUBDIR)/bin
INCPATH = $(PUBDIR)/inc
LIBPATH = $(PUBDIR)/lib
OBJPATH2 = ..\/pub\/obj
OBJ = ${cppfiles:%.cpp=%.o} 
LIBOBJ = $(addprefix $(OBJPATH)/, $(OBJ))

CFLAGS = -g -fPIC -Wno-deprecated -Wall -DLINUX_OS -DRWSTD_MULTI_THREAD -D_LIBC_REENTRANT -D_REENTRANT -D_THREAD_SAFE -DBBS_MODULE -DPRINT_PROTO -pg
INCLUDE += -I. -I$(INCPATH)

SO_LINK_FLAGS = -shared -o
LIB_LINK_FLAGS = -rc
SO_CREA_CMD = ld
LIB_CREA_CMD = ar

all: depend mkd  $(TARGET_LIB)
lib: depend mkd $(TARGET_LIB)

depend:
	@$(CXX) -MM $(INCLUDE) $(SRCS) | sed 's/^.*\.o:/$(OBJPATH2)\/&/g' > .depend

-include .depend

mkd:
	@mkdir -p $(OBJPATH)
	@mkdir -p $(BINPATH)
	@mkdir -p $(INCPATH)
	@mkdir -p $(LIBPATH)

$(OBJPATH)/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $(firstword $^)
 

$(TARGET_LIB): $(LIBOBJ)
	$(LIB_CREA_CMD) $(LIB_LINK_FLAGS) $(LIBPATH)/$@  $^ $(LIB)

clean:
	rm -f $(LIBPATH)/$(TARGET_LIB)
	rm -f $(OBJPATH)/$(LIBOBJ)

