/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include <dlfcn.h>
#include <memory>
#include <string>

namespace qti {

class DynamicLoading final {
  private:
    static void closeDynamicLibrary(void* handle) {
        if (handle != nullptr) {
            dlclose(handle);
        }
    }

  public:
    using DlHandle = std::unique_ptr<void, void (*)(void*)>;

    static DlHandle openLibrary(const std::string& path, int flags) {
        void* handle = dlopen(path.c_str(), flags);

        if (handle == nullptr) {
            return {nullptr, closeDynamicLibrary};
        }

        return {handle, closeDynamicLibrary};
    }
};

}  // namespace qti
