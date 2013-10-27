build:
	node-gyp rebuild

clean:
	rm -rf ./build
	rm -rf ./bin/*

.PHONY: build