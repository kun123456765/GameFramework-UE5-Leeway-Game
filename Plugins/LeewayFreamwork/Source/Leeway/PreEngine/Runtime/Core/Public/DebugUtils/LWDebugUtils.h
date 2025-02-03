//--------------------
// kun 2025.01.12
//--------------------

#pragma once

#include "DrawDebugHelpers.h"

namespace NSLeeway
{
    extern int DrawDebugLevel_All;
}

namespace NSLeeway
{
    void DrawDebugLine(int DebugLevel, const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugPoint(int DebugLevel, const UWorld* InWorld, FVector const& Position, float Size, FColor const& PointColor, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawDebugDirectionalArrow(int DebugLevel, const UWorld* InWorld, FVector const& LineStart, FVector const& LineEnd, float ArrowSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, const FQuat& Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugCoordinateSystem(int DebugLevel, const UWorld* InWorld, FVector const& AxisLoc, FRotator const& AxisRot, float Scale, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugCrosshairs(int DebugLevel, const UWorld* InWorld, FVector const& AxisLoc, FRotator const& AxisRot, float Scale, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawDebugCircle(int DebugLevel, const UWorld* InWorld, const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f, bool bDrawAxis = true);

    void DrawDebugCircle(int DebugLevel, const UWorld* InWorld, FVector Center, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f, FVector YAxis = FVector(0.f, 1.f, 0.f), FVector ZAxis = FVector(0.f, 0.f, 1.f), bool bDrawAxis = true);

    void DrawDebugCircleArc(int DebugLevel, const UWorld* InWorld, FVector const& Center, float Radius, FVector const& Direction, float AngleWidth, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebug2DDonut(int DebugLevel, const UWorld* InWorld, const FMatrix& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugSphere(int DebugLevel, const UWorld* InWorld, FVector const& Center, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugCylinder(int DebugLevel, const UWorld* InWorld, FVector const& Start, FVector const& End, float Radius, int32 Segments, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugCone(int DebugLevel, const UWorld* InWorld, FVector const& Origin, FVector const& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugAltCone(int DebugLevel, const UWorld* InWorld, FVector const& Origin, FRotator const& Rotation, float Length, float AngleWidth, float AngleHeight, FColor const& DrawColor, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawDebugString(int DebugLevel, const UWorld* InWorld, FVector const& TextLocation, const FString& Text, class AActor* TestBaseActor = NULL, FColor const& TextColor = FColor::White, float Duration = -1.000000, bool bDrawShadow = false, float FontScale = 1.f);

    void DrawDebugFrustum(int DebugLevel, const UWorld* InWorld, const FMatrix& FrustumToWorld, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawCircle(int DebugLevel, const UWorld* InWorld, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color, float Radius, int32 NumSides, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);

    void DrawDebugCapsule(int DebugLevel, const UWorld* InWorld, FVector const& Center, float HalfHeight, float Radius, const FQuat& Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);

    void DrawDebugCamera(int DebugLevel, const UWorld* InWorld, FVector const& Location, FRotator const& Rotation, float FOVDeg, float Scale = 1.f, FColor const& Color = FColor::White, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawCentripetalCatmullRomSpline(int DebugLevel, const UWorld* InWorld, TConstArrayView<FVector> Points, FColor const& Color, float Alpha = 0.5f, int32 NumSamplesPerSegment = 8, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void DrawCentripetalCatmullRomSpline(int DebugLevel, const UWorld* InWorld, TConstArrayView<FVector> Points, TConstArrayView<FColor> Colors, float Alpha = 0.5f, int32 NumSamplesPerSegment = 8, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

    void FlushDebugStrings(int DebugLevel, const UWorld* InWorld);

    void DrawDebugSolidBox(int DebugLevel, const UWorld* InWorld, FBox const& Box, FColor const& Color, const FTransform& Transform = FTransform::Identity, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawDebugSolidBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawDebugSolidBox(int DebugLevel, const UWorld* InWorld, FVector const& Center, FVector const& Extent, FQuat const& Rotation, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawDebugMesh(int DebugLevel, const UWorld* InWorld, TArray<FVector> const& Verts, TArray<int32> const& Indices, FColor const& Color, bool bPersistent = false, float LifeTime = -1.f, uint8 DepthPriority = 0);

    void DrawDebugSolidPlane(int DebugLevel, const UWorld* InWorld, FPlane const& P, FVector const& Loc, float Size, FColor const& Color, bool bPersistent = false, float LifeTime = -1, uint8 DepthPriority = 0);

    void DrawDebugSolidPlane(int DebugLevel, const UWorld* InWorld, FPlane const& P, FVector const& Loc, FVector2D const& Extents, FColor const& Color, bool bPersistent = false, float LifeTime = -1, uint8 DepthPriority = 0);

    void DrawDebugFloatHistory(int DebugLevel, UWorld const& WorldRef, FDebugFloatHistory const& FloatHistory, FTransform const& DrawTransform, FVector2D const& DrawSize, FColor const& DrawColor, bool const& bPersistent = false, float const& LifeTime = -1.f, uint8 const& DepthPriority = 0);

    void DrawDebugFloatHistory(int DebugLevel, UWorld const& WorldRef, FDebugFloatHistory const& FloatHistory, FVector const& DrawLocation, FVector2D const& DrawSize, FColor const& DrawColor, bool const& bPersistent = false, float const& LifeTime = -1.f, uint8 const& DepthPriority = 0);

    void DrawDebugCanvas2DLine(int DebugLevel, UCanvas* Canvas, const FVector& Start, const FVector& End, const FLinearColor& LineColor);

    void DrawDebugCanvas2DLine2(int DebugLevel, UCanvas* Canvas, const FVector2D& StartPosition, const FVector2D& EndPosition, const FLinearColor& LineColor, const float& LineThickness = 1.f);

    void DrawDebugCanvas2DCircle(int DebugLevel, UCanvas* Canvas, const FVector2D& Center, float Radius, int32 NumSides, const FLinearColor& LineColor, const float& LineThickness = 1.f);

    void DrawDebugCanvas2DBox(int DebugLevel, UCanvas* Canvas, const FBox2D& Box, const FLinearColor& LineColor, const float& LineThickness = 1.f);

    void DrawDebugCanvasLine(int DebugLevel, UCanvas* Canvas, const FVector& Start, const FVector& End, const FLinearColor& LineColor);

    void DrawDebugCanvasCircle(int DebugLevel, UCanvas* Canvas, const FVector& Base, const FVector& X, const FVector& Y, FColor Color, float Radius, int32 NumSides);

    void DrawDebugCanvasHalfCircle(int DebugLevel, UCanvas* Canvas, const FVector& Base, const FVector& X, const FVector& Y, FColor Color, float Radius, int32 NumSides);

    void DrawDebugCanvasWireSphere(int DebugLevel, UCanvas* Canvas, const FVector& Base, FColor Color, float Radius, int32 NumSides);

    void DrawDebugCanvasWireCone(int DebugLevel, UCanvas* Canvas, const FTransform& Transform, float ConeRadius, float ConeAngle, int32 ConeSides, FColor Color);

    void DrawDebugCanvasWireBox(int DebugLevel, UCanvas* Canvas, const FMatrix& Transform, const FBox& Box, FColor Color);

    void DrawDebugCanvasCapsule(int DebugLevel, UCanvas* Canvas, const FMatrix& Transform, float HalfLength, float Radius, const FColor& LineColor);
}

namespace NSLeeway
{
    void DrawDebugCharacter(ACharacter* Character, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);
    void DrawDebugCapsuleComponent(UCapsuleComponent* CapsuleComp, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);
    void DrawDebugSection(UWorld* World, FVector const& Center, float Radius, float DegreeThreshold, FQuat Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0, int Segments = 30);

    void DrawDebugCharacter(int DebugLevel, ACharacter* Character, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);
    void DrawDebugCapsuleComponent(int DebugLevel, UCapsuleComponent* CapsuleComp, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0);
    void DrawDebugSection(int DebugLevel, UWorld* World, FVector const& Center, float Radius, float DegreeThreshold, FQuat Rotation, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0, int Segments = 30);
}