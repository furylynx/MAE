#/bin/bash

echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin
VERSION_MAJOR=$(cat mae.json | jq -r .version_major)
VERSION_MINOR=$(cat mae.json | jq -r .version_minor)
VERSION_PATCH=$(cat mae.json | jq -r .version_patch)
docker build --tag furylynx/mae:$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH --tag .
docker push furylynx/mae:$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH
