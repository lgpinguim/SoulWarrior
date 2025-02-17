// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "MainCharacter.h"

APickup::APickup()
{
	bRotate = true;
	CoinCount =1;
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	UE_LOG(LogTemp,Warning,TEXT("Pickup::OnOverlapBegin()"));

	if(OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			MainCharacter->IncrementCoins(CoinCount);
			MainCharacter->PickupLocations.Add(GetActorLocation());

			Destroy();
		}
	}
	
}

void APickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	
	UE_LOG(LogTemp,Warning,TEXT("Pickup::OnOverlapEnd()"));
}
