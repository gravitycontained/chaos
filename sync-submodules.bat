git submodule update --init
git submodule sync
git submodule update
git submodule foreach git checkout main
git submodule foreach git pull origin main