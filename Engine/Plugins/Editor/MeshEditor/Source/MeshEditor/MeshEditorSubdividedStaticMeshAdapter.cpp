// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MeshEditorSubdividedStaticMeshAdapter.h"
#include "EditableMesh.h"
#include "WireframeMeshComponent.h"


static FColor GetSubdividedEdgeColor( bool bIsSubdividedWireEdge )
{
	return bIsSubdividedWireEdge ? FColor( 0, 0, 51, 204 ) : FColor( 13, 13, 13, 153 );
}


UMeshEditorSubdividedStaticMeshAdapter::UMeshEditorSubdividedStaticMeshAdapter()
{
}


void UMeshEditorSubdividedStaticMeshAdapter::Initialize( UEditableMesh* EditableMesh, UWireframeMesh* InWireframeMesh )
{
	WireframeMesh = InWireframeMesh;
}


void UMeshEditorSubdividedStaticMeshAdapter::OnRebuildRenderMeshStart( const UEditableMesh* EditableMesh, const bool bInvalidateLighting )
{
	for( TObjectIterator<UWireframeMeshComponent> It( RF_ClassDefaultObject, false, EInternalObjectFlags::PendingKill ); It; ++It )
	{
		if( It->GetWireframeMesh() == WireframeMesh )
		{
			if( It->IsRenderStateCreated() )
			{
				check( It->IsRegistered() );
				It->UnregisterComponent();
			}
		}
	}

	WireframeMesh->ReleaseResources();

	// Flush the rendering commands generated by the detachments.
	FlushRenderingCommands();
}


void UMeshEditorSubdividedStaticMeshAdapter::OnRebuildRenderMesh( const UEditableMesh* EditableMesh )
{
	const FSubdivisionLimitData& SubdivisionLimitData = EditableMesh->GetSubdivisionLimitData();

	WireframeMesh->Reset();

	if( EditableMesh->IsPreviewingSubdivisions() )
	{
		int32 VertexIndex = 0;
		for( const FVector& VertexPosition : SubdivisionLimitData.VertexPositions )
		{
			const FVertexID VertexID( VertexIndex );
			WireframeMesh->AddVertex( VertexID );
			WireframeMesh->SetVertexPosition( VertexID, VertexPosition );
			VertexIndex++;
		}

		// Not going to perform backface culling (we would need precalculated edge normals to do that, and ideally
		// two edge instances - one per adjacent polygon), so just use a zero vector for the polygon normal.
		const FPolygonID DummyPolygonID( 0 );
		WireframeMesh->AddPolygon( DummyPolygonID );
		WireframeMesh->SetPolygonNormal( DummyPolygonID, FVector::ZeroVector );

		int32 EdgeIndex = 0;
		for( const FSubdividedWireEdge& SubdividedWireEdge : SubdivisionLimitData.SubdividedWireEdges )
		{
			const FEdgeID EdgeID( EdgeIndex );
			WireframeMesh->AddEdge( EdgeID );
			WireframeMesh->SetEdgeVertices( EdgeID, FVertexID( SubdividedWireEdge.EdgeVertex0PositionIndex ), FVertexID( SubdividedWireEdge.EdgeVertex1PositionIndex ) );
			WireframeMesh->SetEdgeColor( EdgeID, GetSubdividedEdgeColor( SubdividedWireEdge.CounterpartEdgeID != FEdgeID::Invalid ) );
			WireframeMesh->AddEdgeInstance( EdgeID, DummyPolygonID );
			EdgeIndex++;
		}
	}
}


void UMeshEditorSubdividedStaticMeshAdapter::OnRebuildRenderMeshFinish( const UEditableMesh* EditableMesh, const bool bRebuildBoundsAndCollision, const bool bIsPreviewRollback )
{
	WireframeMesh->InitResources();

	for( TObjectIterator<UWireframeMeshComponent> It( RF_ClassDefaultObject, false, EInternalObjectFlags::PendingKill ); It; ++It )
	{
		if( It->GetWireframeMesh() == WireframeMesh )
		{
			if( !It->IsRenderStateCreated() )
			{
				It->RegisterComponent();
			}
		}
	}
}


void UMeshEditorSubdividedStaticMeshAdapter::OnStartModification( const UEditableMesh* EditableMesh, const EMeshModificationType MeshModificationType, const EMeshTopologyChange MeshTopologyChange )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnEndModification( const UEditableMesh* EditableMesh )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnReindexElements( const UEditableMesh* EditableMesh, const FElementIDRemappings& Remappings )
{
}


bool UMeshEditorSubdividedStaticMeshAdapter::IsCommitted( const UEditableMesh* EditableMesh ) const
{
	return false;
}


bool UMeshEditorSubdividedStaticMeshAdapter::IsCommittedAsInstance( const UEditableMesh* EditableMesh ) const
{
	return false;
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCommit( UEditableMesh* EditableMesh )
{
}


UEditableMesh* UMeshEditorSubdividedStaticMeshAdapter::OnCommitInstance( UEditableMesh* EditableMesh, UPrimitiveComponent* ComponentToInstanceTo )
{
	return nullptr;
}


void UMeshEditorSubdividedStaticMeshAdapter::OnRevert( UEditableMesh* EditableMesh )
{
}


UEditableMesh* UMeshEditorSubdividedStaticMeshAdapter::OnRevertInstance( UEditableMesh* EditableMesh )
{
	return nullptr;
}


void UMeshEditorSubdividedStaticMeshAdapter::OnPropagateInstanceChanges( UEditableMesh* EditableMesh )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnDeleteVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnDeleteOrphanVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCreateEmptyVertexRange( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCreateVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCreateVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCreateEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnDeleteEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnSetEdgesVertices( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCreatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnDeletePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnChangePolygonVertexInstances( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnCreatePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnDeletePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs )
{
}


void UMeshEditorSubdividedStaticMeshAdapter::OnRetriangulatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs )
{
}
