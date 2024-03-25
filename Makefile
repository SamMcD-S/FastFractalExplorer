OBJS = Fractal.o
SRCS = Fractal.c
BUILD_ARGS = -g
Fractal.o: Fractal.c
	mex $(BUILD_ARGS) -c Fractal.c
%.mexmaci64:%.c $(OBJS)
	mex $(BUILD_ARGS)  $< $(OBJS)
%: %.c $(SRCS)
	clang $< $(SRCS) $(BUILD_ARGS) -o $@
mexBuild:Interface.mexmaci64
clean:
	rm *.o *.mexmaci64 unitTest
