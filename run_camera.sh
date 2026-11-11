#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

cmake -S "$project_root" -B "$project_root/build"
cmake --build "$project_root/build" --target camera_preview
exec "$project_root/build/camera_preview"
