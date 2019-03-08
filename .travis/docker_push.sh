#/bin/bash

check_err() {
   if [ $1 -ne 0 ]; then
      echo "Failure: $2"
      exit $1
   fi
}

echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin
check_err $? "docker login"

VERSION_MAJOR=$(cat mae.json | jq -r .version_major)
VERSION_MINOR=$(cat mae.json | jq -r .version_minor)
VERSION_PATCH=$(cat mae.json | jq -r .version_patch)

docker build --tag furylynx/mae:$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH --tag furylynx/mae:latest .
check_err $? "docker build"

docker push furylynx/mae:$VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH
check_err $? "docker push $VERSION_MAJOR.$VERSION_MINOR.$VERSION_PATCH"

docker push furylynx/mae:latest
check_err $? "docker push latest"
