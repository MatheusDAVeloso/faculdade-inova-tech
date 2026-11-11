$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $PSScriptRoot
$buildDirectory = Join-Path $projectRoot "build/windows"
$configureArguments = @("-S", $projectRoot, "-B", $buildDirectory)

if ($env:OpenCV_DIR) {
    $configureArguments += "-DOpenCV_DIR=$env:OpenCV_DIR"
}

& cmake @configureArguments
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

& cmake --build $buildDirectory --config Release --target camera_preview
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Write-Host "Windows executable built in $buildDirectory"
