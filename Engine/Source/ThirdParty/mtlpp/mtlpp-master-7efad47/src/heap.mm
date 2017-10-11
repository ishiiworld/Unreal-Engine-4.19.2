/*
 * Copyright 2016-2017 Nikolay Aleksiev. All rights reserved.
 * License: https://github.com/naleksiev/mtlpp/blob/master/LICENSE
 */
// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
// Modifications for Unreal Engine

#include "heap.hpp"
#include <Metal/MTLHeap.h>

namespace mtlpp
{
    uint32_t HeapDescriptor::GetSize() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return uint32_t([(MTLHeapDescriptor*)m_ptr size]);
#else
        return 0;
#endif

    }

    StorageMode HeapDescriptor::GetStorageMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return StorageMode([(MTLHeapDescriptor*)m_ptr storageMode]);
#else
        return StorageMode(0);
#endif

    }

    CpuCacheMode HeapDescriptor::GetCpuCacheMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return CpuCacheMode([(MTLHeapDescriptor*)m_ptr cpuCacheMode]);
#else
        return CpuCacheMode(0);
#endif

    }

    void HeapDescriptor::SetSize(uint32_t size) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        [(MTLHeapDescriptor*)m_ptr setSize:size];
#endif

    }

    void HeapDescriptor::SetStorageMode(StorageMode storageMode) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        [(MTLHeapDescriptor*)m_ptr setStorageMode:MTLStorageMode(storageMode)];
#endif

    }

    void HeapDescriptor::SetCpuCacheMode(CpuCacheMode cpuCacheMode) const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        [(MTLHeapDescriptor*)m_ptr setCpuCacheMode:MTLCPUCacheMode(cpuCacheMode)];
#endif

    }

    ns::String Heap::GetLabel() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return [(id<MTLHeap>)m_ptr label];
#else
        return nullptr;
#endif

    }

    Device Heap::GetDevice() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return [(id<MTLHeap>)m_ptr device];
#else
        return nullptr;
#endif

    }

    StorageMode Heap::GetStorageMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return StorageMode([(id<MTLHeap>)m_ptr storageMode]);
#else
        return StorageMode(0);
#endif

    }

    CpuCacheMode Heap::GetCpuCacheMode() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return CpuCacheMode([(id<MTLHeap>)m_ptr cpuCacheMode]);
#else
        return CpuCacheMode(0);
#endif

    }

    uint32_t Heap::GetSize() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return uint32_t([(id<MTLHeap>)m_ptr size]);
#else
        return 0;
#endif

    }

    uint32_t Heap::GetUsedSize() const
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return uint32_t([(id<MTLHeap>)m_ptr usedSize]);
#else
        return 0;
#endif

    }
	
	uint32_t Heap::GetCurrentAllocatedSize() const
	{
		Validate();
#if MTLPP_IS_AVAILABLE(10_13, 11_0)
		return uint32_t([(id<MTLHeap>)m_ptr currentAllocatedSize]);
#else
		return GetSize();
#endif
	}

    void Heap::SetLabel(const ns::String& label)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        [(id<MTLHeap>)m_ptr setLabel:(NSString*)label.GetPtr()];
#endif

    }

    uint32_t Heap::MaxAvailableSizeWithAlignment(uint32_t alignment)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return uint32_t([(id<MTLHeap>)m_ptr maxAvailableSizeWithAlignment:alignment]);
#else
        return 0;
#endif

    }

    Buffer Heap::NewBuffer(uint32_t length, ResourceOptions options)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return [(id<MTLHeap>)m_ptr newBufferWithLength:length options:MTLResourceOptions(options)];
#else
        return nullptr;
#endif

    }

    Texture Heap::NewTexture(const TextureDescriptor& desc)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return [(id<MTLHeap>)m_ptr newTextureWithDescriptor:(MTLTextureDescriptor*)desc.GetPtr()];
#else
        return nullptr;
#endif

    }

    PurgeableState Heap::SetPurgeableState(PurgeableState state)
    {
        Validate();
#if MTLPP_IS_AVAILABLE(10_13, 10_0)
        return PurgeableState([(id<MTLHeap>)m_ptr setPurgeableState:MTLPurgeableState(state)]);
#else
        return PurgeableState(0);
#endif

    }
}
