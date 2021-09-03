//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2018 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#ifndef HEADER_ClothingCookedPhysX3Param_0p5_h
#define HEADER_ClothingCookedPhysX3Param_0p5_h

#include "NvParametersTypes.h"

#ifndef NV_PARAMETERIZED_ONLY_LAYOUTS
#include "nvparameterized/NvParameterized.h"
#include "nvparameterized/NvParameterizedTraits.h"
#include "NvParameters.h"
#include "NvTraitsInternal.h"
#endif

namespace nvidia
{
namespace parameterized
{

#if PX_VC
#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())
#endif

namespace ClothingCookedPhysX3Param_0p5NS
{

struct PhaseDesc_Type;
struct SetDesc_Type;
struct FabricGPU_Type;

struct F32_DynamicArray1D_Type
{
	float* buf;
	bool isAllocated;
	int32_t elementSize;
	int32_t arraySizes[1];
};

struct U32_DynamicArray1D_Type
{
	uint32_t* buf;
	bool isAllocated;
	int32_t elementSize;
	int32_t arraySizes[1];
};

struct SetDesc_DynamicArray1D_Type
{
	SetDesc_Type* buf;
	bool isAllocated;
	int32_t elementSize;
	int32_t arraySizes[1];
};

struct PhaseDesc_DynamicArray1D_Type
{
	PhaseDesc_Type* buf;
	bool isAllocated;
	int32_t elementSize;
	int32_t arraySizes[1];
};

struct FabricGPU_DynamicArray1D_Type
{
	FabricGPU_Type* buf;
	bool isAllocated;
	int32_t elementSize;
	int32_t arraySizes[1];
};

struct SetDesc_Type
{
	uint32_t fiberEnd;
	uint32_t longestFiber;
	uint32_t shortestFiber;
	uint32_t numEdges;
	float avgEdgeLength;
	uint32_t avgFiberLength;
};
struct PhaseDesc_Type
{
	uint32_t phaseType;
	uint32_t setIndex;
	uint32_t restValueOffset;
};
struct FabricGPU_Type
{
	void* fabricGPU;
	void* factory;
};

struct ParametersStruct
{

	uint32_t physicalMeshId;
	uint32_t numVertices;
	F32_DynamicArray1D_Type deformableRestLengths;
	U32_DynamicArray1D_Type deformableIndices;
	U32_DynamicArray1D_Type selfCollisionIndices;
	U32_DynamicArray1D_Type selfCollisionNormalIndices;
	U32_DynamicArray1D_Type selfCollisionNormalSetSizes;
	SetDesc_DynamicArray1D_Type deformableSets;
	PhaseDesc_DynamicArray1D_Type deformablePhaseDescs;
	U32_DynamicArray1D_Type tetherAnchors;
	F32_DynamicArray1D_Type tetherLengths;
	F32_DynamicArray1D_Type deformableInvVertexWeights;
	U32_DynamicArray1D_Type virtualParticleIndices;
	F32_DynamicArray1D_Type virtualParticleWeights;
	uint32_t cookedDataVersion;
	void* fabricCPU;
	FabricGPU_DynamicArray1D_Type fabricGPU;
	NvParameterized::Interface* nextCookedData;

};

static const uint32_t checksum[] = { 0x05292657, 0xc602622e, 0xa6989638, 0xf1f9e34f, };

} // namespace ClothingCookedPhysX3Param_0p5NS

#ifndef NV_PARAMETERIZED_ONLY_LAYOUTS
class ClothingCookedPhysX3Param_0p5 : public NvParameterized::NvParameters, public ClothingCookedPhysX3Param_0p5NS::ParametersStruct
{
public:
	ClothingCookedPhysX3Param_0p5(NvParameterized::Traits* traits, void* buf = 0, int32_t* refCount = 0);

	virtual ~ClothingCookedPhysX3Param_0p5();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("ClothingCookedPhysX3Param");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const uint32_t ClassVersion = ((uint32_t)0 << 16) + (uint32_t)5;

	static uint32_t staticVersion(void)
	{
		return ClassVersion;
	}

	uint32_t version(void) const
	{
		return(staticVersion());
	}

	static const uint32_t ClassAlignment = 8;

	static const uint32_t* staticChecksum(uint32_t& bits)
	{
		bits = 8 * sizeof(ClothingCookedPhysX3Param_0p5NS::checksum);
		return ClothingCookedPhysX3Param_0p5NS::checksum;
	}

	static void freeParameterDefinitionTable(NvParameterized::Traits* traits);

	const uint32_t* checksum(uint32_t& bits) const
	{
		return staticChecksum(bits);
	}

	const ClothingCookedPhysX3Param_0p5NS::ParametersStruct& parameters(void) const
	{
		ClothingCookedPhysX3Param_0p5* tmpThis = const_cast<ClothingCookedPhysX3Param_0p5*>(this);
		return *(static_cast<ClothingCookedPhysX3Param_0p5NS::ParametersStruct*>(tmpThis));
	}

	ClothingCookedPhysX3Param_0p5NS::ParametersStruct& parameters(void)
	{
		return *(static_cast<ClothingCookedPhysX3Param_0p5NS::ParametersStruct*>(this));
	}

	virtual NvParameterized::ErrorType getParameterHandle(const char* long_name, NvParameterized::Handle& handle) const;
	virtual NvParameterized::ErrorType getParameterHandle(const char* long_name, NvParameterized::Handle& handle);

	void initDefaults(void);

protected:

	virtual const NvParameterized::DefinitionImpl* getParameterDefinitionTree(void);
	virtual const NvParameterized::DefinitionImpl* getParameterDefinitionTree(void) const;


	virtual void getVarPtr(const NvParameterized::Handle& handle, void*& ptr, size_t& offset) const;

private:

	void buildTree(void);
	void initDynamicArrays(void);
	void initStrings(void);
	void initReferences(void);
	void freeDynamicArrays(void);
	void freeStrings(void);
	void freeReferences(void);

	static bool mBuiltFlag;
	static NvParameterized::MutexType mBuiltFlagMutex;
};

class ClothingCookedPhysX3Param_0p5Factory : public NvParameterized::Factory
{
	static const char* const vptr;

public:

	virtual void freeParameterDefinitionTable(NvParameterized::Traits* traits)
	{
		ClothingCookedPhysX3Param_0p5::freeParameterDefinitionTable(traits);
	}

	virtual NvParameterized::Interface* create(NvParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(ClothingCookedPhysX3Param_0p5), ClothingCookedPhysX3Param_0p5::ClassAlignment);
		if (!NvParameterized::IsAligned(newPtr, ClothingCookedPhysX3Param_0p5::ClassAlignment))
		{
			NV_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class ClothingCookedPhysX3Param_0p5");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(ClothingCookedPhysX3Param_0p5)); // always initialize memory allocated to zero for default values
		return NV_PARAM_PLACEMENT_NEW(newPtr, ClothingCookedPhysX3Param_0p5)(paramTraits);
	}

	virtual NvParameterized::Interface* finish(NvParameterized::Traits* paramTraits, void* bufObj, void* bufStart, int32_t* refCount)
	{
		if (!NvParameterized::IsAligned(bufObj, ClothingCookedPhysX3Param_0p5::ClassAlignment)
		        || !NvParameterized::IsAligned(bufStart, ClothingCookedPhysX3Param_0p5::ClassAlignment))
		{
			NV_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class ClothingCookedPhysX3Param_0p5");
			return 0;
		}

		// Init NvParameters-part
		// We used to call empty constructor of ClothingCookedPhysX3Param_0p5 here
		// but it may call default constructors of members and spoil the data
		NV_PARAM_PLACEMENT_NEW(bufObj, NvParameterized::NvParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (ClothingCookedPhysX3Param_0p5*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (ClothingCookedPhysX3Param_0p5::staticClassName());
	}

	virtual uint32_t getVersion()
	{
		return (ClothingCookedPhysX3Param_0p5::staticVersion());
	}

	virtual uint32_t getAlignment()
	{
		return (ClothingCookedPhysX3Param_0p5::ClassAlignment);
	}

	virtual const uint32_t* getChecksum(uint32_t& bits)
	{
		return (ClothingCookedPhysX3Param_0p5::staticChecksum(bits));
	}
};
#endif // NV_PARAMETERIZED_ONLY_LAYOUTS

} // namespace parameterized
} // namespace nvidia

#if PX_VC
#pragma warning(pop)
#endif

#endif
