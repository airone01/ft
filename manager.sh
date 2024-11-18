#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

usage() {
	echo -e "${BLUE}Git Project Manager 📦${NC}"
	echo -e "Usage:"
	echo -e "  $0 add <repo-url> <project-name> ${GREEN}# Add project to central repo${NC}"
	echo -e "  $0 extract <project-name>        ${GREEN}# Extract project for submission${NC}"
	exit 1
}

add_project() {
	REPO_URL=$1
	PROJECT_NAME=$2

	echo -e "${BLUE}🚀 Adding project ${PROJECT_NAME}...${NC}"

	git remote add "${PROJECT_NAME}" "${REPO_URL}"
	if ! git fetch "${PROJECT_NAME}"; then
		echo -e "${RED}❌ Failed to fetch repository${NC}"
		exit 1
	fi

	echo -e "${BLUE}📦 Reorganizing project structure...${NC}"
	if ! git filter-branch --tree-filter "
        mkdir -p ${PROJECT_NAME}/
        mv * ${PROJECT_NAME}/ 2>/dev/null || true
        " "${PROJECT_NAME}/main"; then
		echo -e "${RED}❌ Failed to reorganize project${NC}"
		exit 1
	fi

	echo -e "${BLUE}🔄 Merging project history...${NC}"
	if ! git merge "${PROJECT_NAME}/main" --allow-unrelated-histories -m "Merge project ${PROJECT_NAME}"; then
		echo -e "${RED}❌ Merge failed. Resolve conflicts and complete merge manually${NC}"
		exit 1
	fi

	git remote remove "${PROJECT_NAME}"
	echo -e "${GREEN}✅ Successfully added ${PROJECT_NAME}${NC}"
}

extract_project() {
	PROJECT_NAME=$1

	echo -e "${BLUE}📤 Extracting ${PROJECT_NAME}...${NC}"

	git clone --sparse . "../${PROJECT_NAME}-extracted"
	cd "../${PROJECT_NAME}-extracted" || exit
	git sparse-checkout set "${PROJECT_NAME}"

	mv "${PROJECT_NAME}"/* .
	rm -r "${PROJECT_NAME}"

	echo -e "${GREEN}✅ Project extracted to ../${PROJECT_NAME}-extracted${NC}"
}

case "$1" in
"add")
	if [ "$#" -ne 3 ]; then
		usage
	fi
	add_project "$2" "$3"
	;;
"extract")
	if [ "$#" -ne 2 ]; then
		usage
	fi
	extract_project "$2"
	;;
*)
	usage
	;;
esac
