PROJECT_NAME    =absent
VERSION         =0.0.1

PROFILE                 =../profiles/common
BUILD_TESTING           =true
CONAN_PACKAGE_REFERENCE =${PROJECT_NAME}/${VERSION}@rvarago/stable

.PHONY: all conan-upload conan-package env-conan-package test install compile gen dep mk clean env env-test

all: compile

env:
	docker build -t ${PROJECT_NAME} .

env-test: env
	docker run --rm ${PROJECT_NAME}

env-conan-package: env
	docker run --rm ${PROJECT_NAME} make conan-package

install: compile
	cd build && cmake --build . --target install

conan-package: test
	conan create . ${CONAN_PACKAGE_REFERENCE}

conan-upload: conan-package
	conan upload --force ${CONAN_PACKAGE_REFERENCE} --all --retry 3 --retry-wait 10 --confirm -r ${REMOTE}

test: compile
	cd build && ctest .

compile: gen
	cd build && cmake --build .

gen: dep
	cd build && cmake -D BUILD_TESTING=${BUILD_TESTING} ..

dep: mk
	cd build && conan install .. --build=missing -pr ${PROFILE}

mk:
	-mkdir build

clean:
	rm -rf build
