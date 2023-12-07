.PHONY: build
.DEFAULT_GOAL := help

ROOT_DIR=${PWD}

PROJ=tanks

help:
	@echo "Type: make [rule]. Available options are:"
	@echo ""
	@echo "- help"
	@echo "- format"
	@echo "- clean"
	@echo ""
	@echo "- build-ios"
	@echo "- build-tvos"
	@echo "- build-macos"
	@echo ""
	@echo "- deploy-ios"
	@echo "- deploy-tvos"
	@echo ""

format:
	clang-format -style file -i Source/**

clean:
	rm -rf build_*

build-ios:
	rm -rf build_ios_arm64/
	axmol build -p ios -a arm64 -c

build-tvos:
	rm -rf build_tvos_arm64/
	axmol build -p tvos -a arm64 -c

build-macos:
	rm -rf build_arm64/
	axmol build -c

deploy-ios:
	rm -rf build_ios_arm64/
	axmol build -p ios -a arm64 -c

	cd build_ios_arm64 && \
		xcodebuild -project ${PROJ}.xcodeproj -scheme ${PROJ} -sdk iphoneos

	cd build_ios_arm64 && \
		xcodebuild archive -project ${PROJ}.xcodeproj -scheme ${PROJ} -archivePath ${PROJ}.xcarchive

	cd build_ios_arm64 && \
		xcodebuild -exportArchive -archivePath ${PROJ}.xcarchive -exportOptionsPlist ../proj.ios_mac/ios/exportoptions-prod.plist -exportPath .

	cd build_ios_arm64 && \
		xcrun altool --upload-app -f ${PROJ}.ipa -t ios -u paulocoutinhox@gmail.com -p ${APPLE_SPECIFIC_PASSWORD}

deploy-tvos:
	rm -rf build_tvos_arm64/
	axmol build -p tvos -a arm64 -c

	cd build_tvos_arm64 && \
		xcodebuild -project ${PROJ}.xcodeproj -scheme ${PROJ} -sdk appletvos

	cd build_tvos_arm64 && \
		xcodebuild archive -project ${PROJ}.xcodeproj -scheme ${PROJ} -archivePath ${PROJ}.xcarchive

	cd build_tvos_arm64 && \
		xcodebuild -exportArchive -archivePath ${PROJ}.xcarchive -exportOptionsPlist ../proj.ios_mac/ios/exportoptions-prod.plist -exportPath .

	cd build_tvos_arm64 && \
		xcrun altool --upload-app -f ${PROJ}.ipa -t tvos -u paulocoutinhox@gmail.com -p ${APPLE_SPECIFIC_PASSWORD}

