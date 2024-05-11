// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUEBLITZ_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	/* Visibility Specifiers:
	* VisibleAnywhere: Makes the property visible in all details panels of the editor and Blueprints.
	* VisibleDefaultsOnly: Makes the property visible only in the "Defaults" section of details panels.
	* EditAnywhere: Allows editing the property value directly in the editor.
	* EditDefaultsOnly: Allows editing the property value only in the "Defaults" section.
	* BlueprintReadOnly: Makes the property accessible for reading in Blueprints but not editable.
	* BlueprintReadWrite: Makes the property fully accessible for reading and writing in Blueprints.
	* Category: Groups related properties together under a specific category in the editor.
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health;

public:	
	UFUNCTION(BlueprintCallable, Category="Attributes")
	bool ApplyHealthChange(float Delta);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
};

