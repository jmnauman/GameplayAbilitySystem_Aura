


#include "Actor/PointCollection.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"

#define ADD_POINT(PointVar, PointName) \
	PointVar = CreateDefaultSubobject<USceneComponent>(TEXT(PointName)); \
	Points.Add(PointVar); \
	PointVar->SetupAttachment(GetRootComponent());

APointCollection::APointCollection()
{
	PrimaryActorTick.bCanEverTick = false;

	Pt0 = CreateDefaultSubobject<USceneComponent>("Point0");
	Points.Add(Pt0);
	SetRootComponent(Pt0);
	
	ADD_POINT(Pt1, "Point1");
	ADD_POINT(Pt2, "Point2");
	ADD_POINT(Pt3, "Point3");
	ADD_POINT(Pt4, "Point4");
	ADD_POINT(Pt5, "Point5");
	ADD_POINT(Pt6, "Point6");
	ADD_POINT(Pt7, "Point7");
	ADD_POINT(Pt8, "Point8");
	ADD_POINT(Pt9, "Point10");
}

TArray<USceneComponent*> APointCollection::GetGroundPoints(const FVector& GroundLocation, int32 NumPoints,
	float YawOverride)
{
	NumPoints = FGenericPlatformMath::Min(NumPoints,Points.Num());
	
	TArray<USceneComponent*> ArrayCopy;
	
	for (USceneComponent* Pt : Points)
	{
		if (ArrayCopy.Num() > NumPoints) return ArrayCopy;
		
		FVector Location = Pt->GetComponentLocation();
		if (Pt != Pt0)
		{
			FVector ToPoint = Location - Pt0->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Pt->SetWorldLocation(Pt0->GetComponentLocation() + ToPoint);
		}
		
		Location = Pt->GetComponentLocation();
		const FVector RaisedLocation = FVector(Location.X, Location.Y, Location.Z + 500.f);
		const FVector LoweredLocation = FVector(Location.X, Location.Y, Location.Z - 500.f);
		
		FHitResult HitResult;
		TArray<AActor*> IgnoreActors;
		UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
			this, 
			IgnoreActors, 
			TArray<AActor*>(), 
			1500.f, 
			GetActorLocation());
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByProfile(
			HitResult, 
			RaisedLocation, 
			LoweredLocation, 
			FName("BlockAll"), 
			QueryParams);
		
		const FVector AdjustedLocation = FVector(Location.X, Location.Y, HitResult.ImpactPoint.Z);
		Pt->SetWorldLocation(AdjustedLocation);
		Pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));
		
		ArrayCopy.Add(Pt);
	}
	
	return ArrayCopy;
}

void APointCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

