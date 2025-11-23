# Makefile for the project

.PHONY: install install-hooks build-kuznechik build-lib setup clean-venv clean-dot-directories clean-pycache clean-kuznechik clean-lib clean-all run-pre-commit test

# Variables
PYTHON_VERSION = python3.10
VENV_DIR = venv
PYTHON = $(VENV_DIR)/bin/python3
PIP = $(VENV_DIR)/bin/pip

# Create virtual environment and install dependencies
install:
	@echo "Creating virtual environment with $(PYTHON_VERSION)..."
	$(PYTHON_VERSION) -m venv $(VENV_DIR)
	@echo "Installing dependencies from requirements.txt..."
	$(PIP) install -r requirements.txt

# Install pre-commit hooks
install-hooks:
	@echo "Installing pre-commit hooks..."
	$(VENV_DIR)/bin/pre-commit install

# Build Kuznechik library
build-kuznechik:
	@echo "Building Kuznechik library..."
	mkdir -p lib
	g++ -DDEBUG -fPIC -shared -o lib/kuznechik.so src/kuznechik_crypto/encryption/kuznechik.cpp

# Build all libraries
build-lib: build-kuznechik
	@echo "All libraries built."

# Install project setup (create venv, install dependencies, install pre-commit hooks, build library)
setup: install install-hooks build-lib
	@echo "Project setup complete!"

# Clean virtual environment
clean-venv:
	@echo "Removing virtual environment..."
	rm -rf $(VENV_DIR)

# Clean dot directories (.pytest_cache)
clean-dot-directories:
	@echo "Removing dot directories (.pytest_cache)..."
	rm -rf .pytest_cache

# Clean __pycache__ directories from src and test directories
clean-pycache:
	@echo "Removing __pycache__ directories from src and tests..."
	rm -rf $(shell find src tests -type d -name '__pycache__')

# Clean compiled Kuznechik library
clean-kuznechik:
	@echo "Removing Kuznechik library..."
	rm -f lib/kuznechik.so

# Clean all compiled libraries
clean-lib: clean-kuznechik
	@echo "All compiled libraries cleaned."

# Clean all (venv, dot directories, __pycache__, compiled libraries)
clean-all: clean-venv clean-dot-directories clean-pycache clean-lib
	@echo "Complete clean done!"

# Run pre-commit for all files
run-pre-commit: build-lib
	@echo "Running pre-commit for all files..."
	$(VENV_DIR)/bin/pre-commit run --all-files

# Run test (builds libraries first)
test: build-lib
	@echo "Running tests..."
	$(PYTHON) -m pytest tests
