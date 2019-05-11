PROJECT_NAME=absent
PROFILE=../profiles/common

.PHONY: all test compile gen dep mk clean env env-test

all: compile

env:
	docker build -t ${PROJECT_NAME}:0.1 -f Dockerfile .

env-test: env
	docker run --rm -t ${PROJECT_NAME}:0.1

test: compile
	cd build && ctest .

compile: gen
	cd build && cmake --build .

gen: dep
	cd build && cmake ..

dep: mk
	cd build && conan install .. --build=missing -pr ${PROFILE}

mk:
	-mkdir build

clean:
	rm -rf build
